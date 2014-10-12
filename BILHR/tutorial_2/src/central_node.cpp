/*
     Description: A node for sending and receiving sensorimotor data from the NAO robot.
 */

/*
    This code is presented to you by:
        Diego Rodriguez
        Wolfgang Burger
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
#include "BILHR_ros/Detection.h"

using namespace std;
using namespace cv;
using namespace sensor_msgs;
using namespace message_filters;

namespace enc = sensor_msgs::image_encodings;


// subscribers to tactile and touch sensors
ros::Subscriber tactile_sub;
ros::Subscriber bumper_sub;

// publisher to robot joints for sending the target joint angles
ros::Publisher target_joint_state_pub;

// joint stiffnesses
ros::Publisher stiffness_pub;

// detection publisher (x and y coordinate of detected blob
ros::Publisher detection_pub;

// received motor state of the HEAD
double motor_head_in[HEAD_JOINTS];

// received motor state of the LEFT ARM
double motor_l_arm_in[L_ARM_JOINTS];

// received motor state of the RIGHT ARM
double motor_r_arm_in[R_ARM_JOINTS];

// label of the GUI window showing the raw image of NAO's camera
static const char cam_window[] = "NAO Camera (raw image)";
static const char cam_window2[] = "NAO Camera (HSV image)";

//forward declaration
void sendTargetJointStateLArm(double *des_position);
void sendTargetJointStateRArm(double *des_position);


// set the stiffness
void setStiffness(float value)
{
    cout << "setting stiffnesses (head) to " << value << endl;

    BILHR_ros::JointState target_joint_stiffness;

    // set stiffnesses of HEAD joints
    target_joint_stiffness.name.clear();
    target_joint_stiffness.name.push_back("Head");
    target_joint_stiffness.name.push_back("LArm");
    target_joint_stiffness.name.push_back("RArm");
    target_joint_stiffness.effort.clear();
    for (int i=0; i<HEAD_JOINTS + L_ARM_JOINTS + R_ARM_JOINTS; i++)
        target_joint_stiffness.effort.push_back(value);

    stiffness_pub.publish(target_joint_stiffness);

}


// callback function for vision
void visionCB(const sensor_msgs::ImageConstPtr& msg)
{
    // pointer on OpenCV image
    cv_bridge::CvImagePtr cv_ptr;

    try
    {
        // transform ROS image into OpenCV image
        cv_ptr = cv_bridge::toCvCopy(msg, enc::BGR8);
    }
    catch (cv_bridge::Exception& e)		// throw an error msg. if conversion fails
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    // show the raw camera image
    //imshow(cam_window, cv_ptr->image);
    waitKey(3);

    // create cv Mat from cv bridge
    Mat in_image(cv_ptr->image);

    // declare needed Mats
    Mat hsv_image, img_thresholded, img_smoothed;

    // smooth image with gaussian filter
    GaussianBlur(in_image, img_smoothed, Size(21,21),0,0);

    // convert image to HSV color space
    cvtColor(img_smoothed, hsv_image, CV_BGR2HSV);

    // threshold image to detect blue colors
    cv::inRange(hsv_image, cv::Scalar(95,120,100), cv::Scalar(105,200,255), img_thresholded);

    //cv::inRange(out_image, cv::Scalar(355,255,255), cv::Scalar(360,255,255), img_threshold2);
    //cv::add(img_threshold,img_threshold2,img_sum);

    // get average position of the detected blue pixels to get the center of the blue blob
    int sum_x = 0;
    int sum_y = 0;
    int count = 0;
    int pos_x = 0;
    int pos_y = 0;

    for(int i = 0; i < img_thresholded.rows; i++)
    {
        for(int j = 0; j < img_thresholded.cols/4; j++)
        {
            if(img_thresholded.at<int>(i, j) > 1600 )
            {
                sum_x += j*4;
                sum_y += i;
                count++;
            }

        }
    }

    // check if any blue pixels were found to prevent the division by zero
    if(count > 0)
    {
        pos_x = sum_x / count;
        pos_y = sum_y / count;
    }

    // send a simple messege with x and y coordinate of the detected blob
    BILHR_ros::Detection detection_msg;
    detection_msg.x = pos_x;
    detection_msg.y = pos_y;

    detection_pub.publish(detection_msg);

    // draw a red circle in the center of the detected blob (in the input image)
    circle(in_image, cvPoint(pos_x, pos_y), 5, CV_RGB(255,0,0),3);

    // show the input image with drawed circle
    imshow(cam_window, in_image);

    // show the thresholded image
    imshow(cam_window2, img_thresholded);

    waitKey(3);

}


// callback function for tactile buttons (TBs) on the head
void tactileCB(const BILHR_ros::TactileTouch::ConstPtr& __tactile_touch)
{
    // define the different position vectors
    // for the left arm:
    double R_home_position[] = {0.44, -0.22, 0.477, 0.65, 0.0, 0.0};
    double R_wave_1[] = {0.2,-1.2,1.5, 1.5,-0.4,1.0};
    double R_wave_2[] = {0.2,-1.2,1.5, 0.8,-0.4,1.0};

    // for the right arm:
    double L_home_position[] = {0.44, 0.22, -0.477, -0.65, 0.0, 0.0};
    double L_wave_1[] = {0.2,1.2,-1.5,-1.5,-0.4,1.0};
    double L_wave_2[] = {0.2,1.2,-1.5,-0.8,-0.4,1.0};

    // define waiting times between commands
    ros::Duration waitShort(0.5);
    ros::Duration waitLong(1.5);

    // check TB 3 (rear)
    if (((int)__tactile_touch->button == 3) && ((int)__tactile_touch->state == 1))
    {
        cout << "TB " << (int)__tactile_touch->button << " touched" << endl;
        cout << "Sending both arms to wave" << endl;

        // send positions for both arms and wait some time for every desired position
        sendTargetJointStateLArm(L_home_position);
        sendTargetJointStateRArm(R_home_position);
        waitLong.sleep();

        sendTargetJointStateLArm(L_wave_1);
        sendTargetJointStateRArm(R_wave_1);
        waitLong.sleep();

        sendTargetJointStateLArm(L_wave_2);
        sendTargetJointStateRArm(R_wave_2);
        waitShort.sleep();

        sendTargetJointStateLArm(L_wave_1);
        sendTargetJointStateRArm(R_wave_1);
        waitShort.sleep();

        sendTargetJointStateLArm(L_wave_2);
        sendTargetJointStateRArm(R_wave_2);
        waitShort.sleep();

        sendTargetJointStateLArm(L_wave_1);
        sendTargetJointStateRArm(R_wave_1);
        waitShort.sleep();

        sendTargetJointStateLArm(L_wave_2);
        sendTargetJointStateRArm(R_wave_2);
        waitShort.sleep();

        sendTargetJointStateLArm(L_wave_1);
        sendTargetJointStateRArm(R_wave_1);
        waitShort.sleep();

        sendTargetJointStateLArm(L_home_position);
        sendTargetJointStateRArm(R_home_position);
        waitLong.sleep();

    }

    // check TB 2 (middle)
    if (((int)__tactile_touch->button == 2) && ((int)__tactile_touch->state == 1))
    {
        cout << "TB " << (int)__tactile_touch->button << " touched" << endl;
        cout << "Sending left arm to wave" << endl;

        // command the positions to the left arm and wait some time after each command
        sendTargetJointStateLArm(L_home_position);
        waitLong.sleep();

        sendTargetJointStateLArm(L_wave_1);
        waitLong.sleep();

        sendTargetJointStateLArm(L_wave_2);
        waitShort.sleep();

        sendTargetJointStateLArm(L_wave_1);
        waitShort.sleep();

        sendTargetJointStateLArm(L_wave_2);
        waitShort.sleep();

        sendTargetJointStateLArm(L_wave_1);
        waitShort.sleep();

        sendTargetJointStateLArm(L_wave_2);
        waitShort.sleep();

        sendTargetJointStateLArm(L_wave_1);
        waitShort.sleep();

        sendTargetJointStateLArm(L_home_position);
        waitLong.sleep();

    }

    // check TB 1 (front)
    if (((int)__tactile_touch->button == 1) && ((int)__tactile_touch->state == 1))
    {
        cout << "TB " << (int)__tactile_touch->button << " touched" << endl;
        cout << "Sending left arm to home position" << endl;

        // command left arm to go to the home position
        sendTargetJointStateLArm(L_home_position);
        waitLong.sleep();
    }

}


// callback function for bumpers
void bumperCB(const BILHR_ros::Bumper::ConstPtr& __bumper)
{
    // check each bumper

    cout << "bumper " << (int)__bumper->bumper << endl;

    static bool left_bumper_flag = false;
    static bool right_bumper_flag = false;

    // check left bumper
    if (((int)__bumper->bumper == 1) && ((int)__bumper->state == 1))
    {
        left_bumper_flag = !left_bumper_flag;   // toggle flag

        // do something, e.g.:
        // set / reset stiffness
        if (left_bumper_flag)
            setStiffness(0.005);
        /*
        else
            setStiffness(0.9);  */

    }

    // check right bumper
    if (((int)__bumper->bumper == 0) && ((int)__bumper->state == 1))
    {
        right_bumper_flag = !right_bumper_flag;     // toggle flag



    }

}


// callback function for the head joints
void jointStateCB(const BILHR_ros::JointState::ConstPtr& joint_state)
{
    // buffer for incoming message
    std_msgs::Float32MultiArray buffer;

    // index
    int idx;


    // extract the proprioceptive state of the HEAD
    buffer.data.clear();
    for (int i=0; i<ROBOT_JOINTS; i++)
    {
        if (joint_state->name[i] == "HeadYaw")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << ": " << joint_state->position[i] << endl;
        }
        if (joint_state->name[i] == "HeadPitch")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << ": " << joint_state->position[i] << endl;
        }
    }

    // write data into array
    idx = 0;
    for(vector<float>::const_iterator iter = buffer.data.begin(); iter != buffer.data.end(); ++iter)
    {
        // store into temporary target motor state buffer
        motor_head_in[idx] = *iter;
        idx++;
    }

    // display data on terminal
    cout << "Head joints:  ";
    for (int i=0; i<HEAD_JOINTS; i++)
        cout << motor_head_in[i] << " ";
    cout << endl;


    // extract the proprioceptive state of the LEFT ARM
    buffer.data.clear();
    for (int i=0; i<ROBOT_JOINTS; i++)
    {
        if (joint_state->name[i] == "LShoulderPitch")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }
        if (joint_state->name[i] == "LShoulderRoll")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }
        if (joint_state->name[i] == "LElbowYaw")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }
        if (joint_state->name[i] == "LElbowRoll")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }
        if (joint_state->name[i] == "LWristYaw")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }
        if (joint_state->name[i] == "LHand")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }

    }

    // write data into array
    idx = 0;
    for(vector<float>::const_iterator iter = buffer.data.begin(); iter != buffer.data.end(); ++iter)
    {
        // store into temporary target motor state buffer
        motor_l_arm_in[idx] = *iter;
        idx++;
    }

    // display data on terminal
    cout << "Left arm joints:  ";
    for (int i=0; i<L_ARM_JOINTS; i++)
        cout << motor_l_arm_in[i] << " ";
    cout << endl;


    // extract the proprioceptive state of the RIGHT ARM
    buffer.data.clear();
    for (int i=0; i<ROBOT_JOINTS; i++)
    {
        if (joint_state->name[i] == "RShoulderPitch")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }
        if (joint_state->name[i] == "RShoulderRoll")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }
        if (joint_state->name[i] == "RElbowYaw")
        {
           buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }
        if (joint_state->name[i] == "RElbowRoll")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }
        if (joint_state->name[i] == "RWristYaw")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }
        if (joint_state->name[i] == "RHand")
        {
            buffer.data.push_back(joint_state->position[i]);
            // cout << joint_state->name[i] << endl;
        }

    }

    // write data into array
    idx = 0;
    for(vector<float>::const_iterator iter = buffer.data.begin(); iter != buffer.data.end(); ++iter)
    {
        // store into temporary target motor state buffer
        motor_r_arm_in[idx] = *iter;
        idx++;
    }

    // display data on terminal
    cout << "Right arm joints:  ";
    for (int i=0; i<R_ARM_JOINTS; i++)
        cout << motor_r_arm_in[i] << " ";
    cout << endl;

}


// send commanded joint positions of the HEAD
void sendTargetJointStateHead(double* des_position)
{
    //double dummy[HEAD_JOINTS];  // dummy representing the comanded joint state
    BILHR_ros::JointAnglesWithSpeed target_joint_state;

    // specify the limb
    target_joint_state.joint_names.clear();
    target_joint_state.joint_names.push_back("Head");

    // specifiy the angle
    target_joint_state.joint_angles.clear();
    for (int i=0; i<HEAD_JOINTS; i++)
        target_joint_state.joint_angles.push_back(des_position[i]);

    // set speed
    target_joint_state.speed = 0.2;

    // set the mode of joint change
    target_joint_state.relative = 0;

    // send to robot
    target_joint_state_pub.publish(target_joint_state);

}


// send commanded joint positions of the LEFT ARM
void sendTargetJointStateLArm(double* des_position)
{
    //double new_position[L_ARM_JOINTS];  // dummy representing the comanded joint state

    BILHR_ros::JointAnglesWithSpeed target_joint_state;

    // specify the limb
    target_joint_state.joint_names.clear();
    target_joint_state.joint_names.push_back("LArm");

    // specifiy the angle
    target_joint_state.joint_angles.clear();
    for (int i=0; i<L_ARM_JOINTS; i++)
        target_joint_state.joint_angles.push_back(des_position[i]);

    // set speed
    target_joint_state.speed = 0.2;

    // set the mode of joint change
    target_joint_state.relative = 0;

    // send to robot
    target_joint_state_pub.publish(target_joint_state);

}


// send commanded joint positions of the RIGHT ARM
void sendTargetJointStateRArm(double* des_position)
{
    //double dummy[R_ARM_JOINTS];  // dummy representing the comanded joint state

    BILHR_ros::JointAnglesWithSpeed target_joint_state;

    // specify the limb
    target_joint_state.joint_names.clear();
    target_joint_state.joint_names.push_back("RArm");

    // specifiy the angle
    target_joint_state.joint_angles.clear();
    for (int i=0; i<R_ARM_JOINTS; i++)
        target_joint_state.joint_angles.push_back(des_position[i]);

    // set speed
    target_joint_state.speed = 0.2;

    // set the mode of joint change
    target_joint_state.relative = 0;

    // send to robot
    target_joint_state_pub.publish(target_joint_state);

}


// callback function for key events
void keyCB(const std_msgs::String::ConstPtr& msg)
{
    cout << msg->data.c_str();

    // start the robot behaviour
    if (*(msg->data.c_str()) == '0')
	{
		cout << "keyCB()" << endl;
		
    	
	}

}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "central_node");
    ros::NodeHandle central_node_nh;

    // messaging with the NAO nodes

    // advertise joint stiffnesses
    stiffness_pub = central_node_nh.advertise<BILHR_ros::JointState>("joint_stiffness", 1);

    // subscribe to the joint states
    // the topic is the same as the one of the wrapper node of the NAO robot
    ros::Subscriber joint_state_sub;
    joint_state_sub = central_node_nh.subscribe("joint_states", 1, &jointStateCB);

    // advertise the target joint states
    target_joint_state_pub = central_node_nh.advertise<BILHR_ros::JointAnglesWithSpeed>("joint_angles", 1);    // to NAO robot

    // advertise the detected blob position topic
    detection_pub = central_node_nh.advertise<BILHR_ros::Detection>("detection_topic" , 1);

    // using image_transport to publish and subscribe to images
    image_transport::ImageTransport image_tran(central_node_nh);

    // subscribe to the raw camera image
    image_transport::Subscriber image_sub;
    image_sub = image_tran.subscribe("image_raw", 1, &visionCB);

    // subscribe to tactile and touch sensors
    tactile_sub = central_node_nh.subscribe("tactile_touch", 1, tactileCB);
    bumper_sub = central_node_nh.subscribe("bumper", 1, bumperCB);

    // set up the subscriber for the keyboard
    ros::Subscriber key_sub;
    key_sub = central_node_nh.subscribe("key", 5, keyCB);

    // create a GUI window for the raw camera image
    namedWindow(cam_window, 0);
    namedWindow(cam_window2, 0);

    // set the stiffness of the NAO robot
    setStiffness(0.5);


    ros::spin();

    return 0;
}
