#include <leg_node.h>

/*
     Description: A node for sending and receiving sensorimotor data from the NAO robot.
     Written by: Christoph Klopf
 */


#include <ros/ros.h>

// ROS and OpenCV image processing
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32.h>
#include "std_msgs/String.h"

// own files
#include "robot_config.h"
#include <iostream>
#include <fstream>


using namespace std;
using namespace cv;
using namespace sensor_msgs;
using namespace message_filters;

namespace enc = sensor_msgs::image_encodings;
void sendTargetJointStateLArm(double* jointStates);
void sendDefaultGoalPosition(double *jointStateHead, double *jointStateLArm, double *jointStateLLeg, double *jointStateRArm, double *jointStateRLeg, double speedy);
void kick(double speed, double LHipPitch_loc);
void moveLeg(double speed, double LHipRoll_loc);


// subscribers to tactile and touch sensors
ros::Subscriber tactile_sub;
ros::Subscriber bumper_sub;

// publisher to robot joints for sending the target joint angles
ros::Publisher target_joint_state_pub;

// joint stiffnesses
ros::Publisher stiffness_pub;

// pubish leg position for RL
ros::Publisher LegPosition_pub;

// received motor state of the HEAD
double motor_head_in[HEAD_JOINTS];

// received motor state of the LEFT ARM
double motor_l_arm_in[L_ARM_JOINTS];

// received motor state of the RIGHT ARM
double motor_r_arm_in[R_ARM_JOINTS];

double headStates_def[HEAD_JOINTS] = {-0.045, 0.213};

double larmStates_def[L_ARM_JOINTS] = {1.5, 0.4, 0.064, -0.035, -1.810, 0.1};
double llegStates_def[L_LEG_JOINTS] = {-0.030638, -0.1, 0, 0.631676, -0.21, -0.0};

double rarmStates_def[R_ARM_JOINTS] = {1.690, -1.256, 0.395, 0.034, 1.207, 1.0};
double rlegStates_def[R_LEG_JOINTS] = {0.0583339, -0.26, 0.15796, -0.0923279, 0.0, -0.085};

// variables for kicking
double maxAngel = 0.3;
double minAngel = -0.3;


int moveCount = -1;

double deltaHipRoll = (maxAngel - minAngel)/5.0;

int currentLegPosition = 0;
int oldLegPosition = 0;

bool cmdSentFlag = 0;


// set the stiffness
void setStiffness(float value)
{
    cout << "setting stiffnesses (head) to " << value << endl;

    BILHR_ros::JointState target_joint_stiffness;

    // set stiffnesses of HEAD joints
    target_joint_stiffness.name.clear();
    target_joint_stiffness.name.push_back("Head");
    target_joint_stiffness.effort.clear();
    for (int i=0; i<HEAD_JOINTS; i++)
        target_joint_stiffness.effort.push_back(value);

    // set stiffnesses of larm/rarm
    target_joint_stiffness.name.push_back("LArm");
    for (int i=0; i<L_ARM_JOINTS; i++)
        target_joint_stiffness.effort.push_back(value);

    target_joint_stiffness.name.push_back("RArm");
    for (int i=0; i<R_ARM_JOINTS; i++)
        target_joint_stiffness.effort.push_back(value);

    target_joint_stiffness.name.push_back("LLeg");
    for (int i=0; i<R_ARM_JOINTS; i++)
        target_joint_stiffness.effort.push_back(value);

    target_joint_stiffness.name.push_back("RLeg");
    for (int i=0; i<R_ARM_JOINTS; i++)
        target_joint_stiffness.effort.push_back(value);


    stiffness_pub.publish(target_joint_stiffness);

}

void tactileCB(const BILHR_ros::TactileTouch::ConstPtr& __tactile_touch)
{

    // check TB 3 (rear)
    if (((int)__tactile_touch->button == 3) && ((int)__tactile_touch->state == 1))
    {
        cout<<"Button 3 touched1"<<endl;

        // reset relative move count
        moveCount = 0;
        sendDefaultGoalPosition(headStates_def,larmStates_def,llegStates_def,rarmStates_def,rlegStates_def, 0.2);

        // wait until moved into homeposition
        sleep(3);

        // trigger jointStateCB() to send message
        oldLegPosition = 0;
        cmdSentFlag = 1;

    }

    // check TB 2 (middle)
    if (((int)__tactile_touch->button == 2) && ((int)__tactile_touch->state == 1))
    {
        cout << "TB " << (int)__tactile_touch->button << " touched" << endl;

        // -0.030638, -0.245108, -0.35, 0.631676, -0.21, -0.0
        // double jointStateLLegKicked[L_LEG_JOINTS] = {-0.030638, -0.1, -0.35, 0.631676, -0.21, -0.0};
        kick(0.9,-0.35);  //void kick(double speed, double LHipPitch_loc)
        sleep(3);

       // double llegStates_def[L_LEG_JOINTS] = {-0.030638, -0.345108, 0, 0.631676, -0.316046, 0.105888};

        kick(0.05,0.1);  //void kick(double speed, double LHipPitch_loc)


    }

    // check TB 1 (front)
    if (((int)__tactile_touch->button == 1) && ((int)__tactile_touch->state == 1))
    {
        cout << "TB " << (int)__tactile_touch->button << " touched" << endl;

    }
}


// callback function for bumpers
void bumperCB(const BILHR_ros::Bumper::ConstPtr& __bumper)
{
    // check each bumper

    // received motor state of the HEAD
    double motor_head_in[HEAD_JOINTS];

    double motor_l_arm_in[L_ARM_JOINTS];

    // received motor state of the RIGHT ARM
    double motor_r_arm_in[R_ARM_JOINTS];
    cout << "bumper " << (int)__bumper->bumper << endl;

    static bool left_bumper_flag = false;
    static bool right_bumper_flag = false;

    // check left bumper
    if (((int)__bumper->bumper == 1) && ((int)__bumper->state == 1))
    {
        left_bumper_flag = !left_bumper_flag;   // toggle flag

    }

    // check right bumper
    if (((int)__bumper->bumper == 0) && ((int)__bumper->state == 1))
    {
        right_bumper_flag = !right_bumper_flag;     // toggle flag

        if (right_bumper_flag){
            setStiffness(0.9);
            cout << "set stiffness of head to 0.9" << endl;
        } else {
            setStiffness(0);
            cout << "reset stiffness of head to 0.0" << endl;

        }

    }
}


// callback function for the head joints
void jointStateCB(const BILHR_ros::JointState::ConstPtr& joint_state)
{

    // find leg positions

    double hipRoll = 0.0;

    for (int i=0; i<ROBOT_JOINTS; i++)
        if (joint_state->name[i] == "LHipRoll")
            hipRoll = joint_state->position[i];


    BILHR_ros::LegPosition llegPos;

    double hipthreshold = deltaHipRoll/2.0;


    if (hipRoll < (minAngel+hipthreshold))
        currentLegPosition = 1;
    else if (((minAngel+hipthreshold) <= hipRoll) && (hipRoll < (minAngel+hipthreshold+deltaHipRoll)))
        currentLegPosition = 2;
    else if (((minAngel+hipthreshold+deltaHipRoll) <= hipRoll) && (hipRoll < (minAngel+hipthreshold+2.0*deltaHipRoll)))
        currentLegPosition = 3;
    else if (((minAngel+hipthreshold+2.0*deltaHipRoll) <= hipRoll) && (hipRoll < (minAngel+hipthreshold+3.0*deltaHipRoll)))
        currentLegPosition = 4;
    else if (((minAngel+hipthreshold+3.0*deltaHipRoll) <= hipRoll))
        currentLegPosition = 5;


    // send leg position only if it changed and command was send
    if((currentLegPosition != oldLegPosition) && cmdSentFlag == 1){
        llegPos.LegPos = currentLegPosition;
        LegPosition_pub.publish(llegPos);

        oldLegPosition = currentLegPosition;
        cmdSentFlag = 0;
    }

}

void moveLegFkt(const BILHR_ros::cmdLegState::ConstPtr& cmdLegState)
{
    cout << "cmdLegState:" << (int)cmdLegState->cmdLegState << endl;

    // move IN
    if (cmdLegState->cmdLegState == 1){
        //limit
        if (moveCount > -1)
            moveCount--;

        double currHipRoll = deltaHipRoll*moveCount + llegStates_def[1];
        moveLeg(0.05,currHipRoll);//void moveLeg(double speed, double LHipRoll_loc)
    }
    // move OUT
    if (cmdLegState->cmdLegState == 2){
        //limit
        if (moveCount < 3)
            moveCount++;

        double currHipRoll = deltaHipRoll*moveCount + llegStates_def[1];
        moveLeg(0.05,currHipRoll);//void moveLeg(double speed, double LHipRoll_loc)
    }

    // only send current leg position if command was sent
    if (cmdLegState->cmdLegState == 1 || cmdLegState->cmdLegState == 2)
        cmdSentFlag = 1;

    // Kick
    if (cmdLegState->cmdLegState == 3){
        kick(0.9,-0.35);  //void kick(double speed, double LHipPitch_loc)
        sleep(3);
        // double llegStates_def[L_LEG_JOINTS] = {-0.030638, -0.345108, 0, 0.631676, -0.316046, 0.105888};
        kick(0.05,0.1);  //void kick(double speed, double LHipPitch_loc)
    }

}

void sendDefaultGoalPosition(double *jointStateHead, double *jointStateLArm, double *jointStateLLeg, double *jointStateRArm, double *jointStateRLeg, double speedy)
{
    BILHR_ros::JointAnglesWithSpeed target_joint_state;

    // specify the limb
    target_joint_state.joint_names.clear();
    target_joint_state.joint_names.push_back("Head");
    target_joint_state.joint_names.push_back("LArm");
    target_joint_state.joint_names.push_back("LLeg");
    target_joint_state.joint_names.push_back("RArm");
    target_joint_state.joint_names.push_back("RLeg");

    // specifiy the angle
    target_joint_state.joint_angles.clear();
    for (int i=0; i<HEAD_JOINTS; i++)
        target_joint_state.joint_angles.push_back(jointStateHead[i]);
    for (int i=0; i<L_ARM_JOINTS; i++)
        target_joint_state.joint_angles.push_back(jointStateLArm[i]);
    for (int i=0; i<L_LEG_JOINTS; i++)
        target_joint_state.joint_angles.push_back(jointStateLLeg[i]);
    for (int i=0; i<R_ARM_JOINTS; i++)
        target_joint_state.joint_angles.push_back(jointStateRArm[i]);
    for (int i=0; i<R_LEG_JOINTS; i++)
        target_joint_state.joint_angles.push_back(jointStateRLeg[i]);

    // set speed
    target_joint_state.speed = speedy;

    // set the mode of joint change
    target_joint_state.relative = 0;

    // send to robot
    target_joint_state_pub.publish(target_joint_state);

}

void kick(double speed, double LHipPitch_loc)
{
    BILHR_ros::JointAnglesWithSpeed target_joint_state;

    // specify the limb
    target_joint_state.joint_names.clear();
    target_joint_state.joint_names.push_back("LHipPitch");

    // specifiy the angle
    target_joint_state.joint_angles.clear();
    target_joint_state.joint_angles.push_back(LHipPitch_loc);

    // set speed
    target_joint_state.speed = speed;

    // set the mode of joint change
    target_joint_state.relative = 0;

    // send to robot
    target_joint_state_pub.publish(target_joint_state);

}

void moveLeg(double speed, double LHipRoll_loc)
{
    BILHR_ros::JointAnglesWithSpeed target_joint_state;

    // specify the limb
    target_joint_state.joint_names.clear();
    target_joint_state.joint_names.push_back("LHipRoll");

    // specifiy the angle
    target_joint_state.joint_angles.clear();
    target_joint_state.joint_angles.push_back(LHipRoll_loc);

    // set speed
    target_joint_state.speed = speed;

    // set the mode of joint change
    target_joint_state.relative = 0;

    // send to robot
    target_joint_state_pub.publish(target_joint_state);

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "leg_node");
    ros::NodeHandle nh;

    // messaging with the NAO nodes

    // advertise joint stiffnesses
    stiffness_pub = nh.advertise<BILHR_ros::JointState>("joint_stiffness", 1);

    // subscribe to the joint states
    // the topic is the same as the one of the wrapper node of the NAO robot
    ros::Subscriber joint_state_sub;
    joint_state_sub = nh.subscribe("joint_states", 1, &jointStateCB);

    // advertise the target joint states
    target_joint_state_pub = nh.advertise<BILHR_ros::JointAnglesWithSpeed>("joint_angles", 1);    // to NAO robot


    LegPosition_pub = nh.advertise<BILHR_ros::LegPosition>("leg_state",1);

    // subscribe to tactile and touch sensors
    tactile_sub = nh.subscribe("tactile_touch", 1, tactileCB);
    bumper_sub = nh.subscribe("bumper", 1, bumperCB);

    // subscribe to cmdLegState
    ros::Subscriber sub = nh.subscribe("cmd_Leg_State",1,moveLegFkt);

    ros::spin();

    return 0;
}
