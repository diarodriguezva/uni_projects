/*
* Tracking
* started by Suraj Nair
*/
#include <QApplication>

#include <stdexcept>
#include <exception>
#include <signal.h>
#include "ros/ros.h"
#include <ros_comm_lib/RosActorsSubscriber.h>
#include <ConfigData.h>
#include <robot_control/MoveJoints.h>


using namespace std;

int main(int argc, char** argv)
{
    try
    {
        ros::init(argc, argv, "visual_servoing");

        ConfigData config;
        config.parse();

        comminterface::RosActorsSubscriber mSub(config.VS_TARGET_TOPIC_NAME);
        mSub.start();

        ros_tum_msgs::ActorVec target;
        std::string type="BALL";
        std::string prop="RED";
        int id=0;
        TargetPoseVec pose;

        ros::NodeHandle n;
        ros::ServiceClient client = n.serviceClient<robot_control::MoveJoints>("/cambot_control/move_joints");
        robot_control::MoveJoints srv;


        double DEG2RAD = 3.141592/180.0;

        double error_x=0.0;
        double error_y=0.0;

        double max_joint_motion_x = 30.0;
        double max_joint_motion_y = 30.0;

        double max_x=320.0;
        double max_y=240.0;

        double move_x;
        double move_y;

        srv.request.q0=0;
        srv.request.q1=0;
        srv.request.q2=0;

        if (client.call(srv))
        {
            if(srv.response.success)
                std::cout << "Move successfull to zero" <<std::endl;
            else
                std::cout << "Move failed to zero" <<std::endl;

        }
        else
        {
            ROS_ERROR("Failed to call service /robot_control/move_joints");
        }

        double q_x=0.0;
        double q_y=0.0;

        double moveThreshold=10.0;

        double step_x;
        double step_y;

        while(true)
        {

            mSub.getActorsData(target);

            if(util::Util::getActorPose(target, type, prop, id, pose))
            {
                std::cout << "Target Found at " << pose[0] << std::endl;

                error_x=pose[0](0)-max_x;
                error_y=pose[0](1)-max_y;

                move_x=(max_joint_motion_x*error_x)/max_x;
                move_y=(max_joint_motion_y*error_y)/max_y;

                std::cout << "Move " << move_x << " " << move_y << std::endl;

//                step_x = (move_x*DEG2RAD)/2.0;
//                step_y = (move_y*DEG2RAD)/2.0;
//                std::cout << "Step " << step_x << " " << step_y << std::endl;

                step_x=0.3;
                step_y=0.3;

                if(move_x > moveThreshold)
                    q_x-=fabs(step_x);
                else if(move_x < -moveThreshold)
                    q_x+=fabs(step_x);


                if(move_y > moveThreshold)
                    q_y+=fabs(step_y);
                else if(move_y < -moveThreshold)
                    q_y-=fabs(step_y);


                //std::cout << "Move rad " << move_x << " " << move_y << std::endl;

                //std::cout << "error " << error_x << " " << error_y << std::endl;

                std::cout << "q_x q_y " << q_x << " " << q_y << std::endl;
                srv.request.q0=q_x;
                srv.request.q1=0.0;
                srv.request.q2=q_y;

                if (client.call(srv))
                {
                    if(srv.response.success)
                    {
                        //std::cout << "Move successfull" <<std::endl;
                    }
                    else
                    {
                        std::cout << "Move failed" <<std::endl;
                    }

                }
                else
                {
                    ROS_ERROR("Failed to call service /robot_control/move_joints");
                    throw;
                }
            }
            else
            {
                std::cout << "Target not found" << std::endl;
            }

            usleep(100);

        }

        mSub.stopThread();


        return 1;

    }
    catch (std::exception& e)
    {

        std::cout << e.what() << endl;
    }

    return 0;
};



