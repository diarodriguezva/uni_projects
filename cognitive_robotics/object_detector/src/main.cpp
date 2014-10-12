/*
* Tracking
* started by Suraj Nair
*/
#include <QApplication>
#include <stdexcept>
#include <exception>
#include <signal.h>
#include <detector/DetectorThread.h>
#include "main.h"
#include <ros_comm_lib/RosActorsSubscriber.h>
#include <ros_comm_lib/util/Util.h>
#include <robot_control/MoveToOS.h>
#include <gripper_control/OpenGripper.h>
#include <gripper_control/CloseGripper.h>

using namespace std;

int main(int argc, char** argv)
{
    try
    {
        ros::init(argc, argv, "object_detector");

        DetectorThread detector;
        detector.start();

        cv::Mat detectImg;
        cv::Mat colorSegImg;
        namedWindow("detector", 1);
        //namedWindow("seg", 1);
        //namedWindow("cont", 1);

        comminterface::RosActorsSubscriber mSub("/object_detector/objects_data");
        mSub.start();

        ros_tum_msgs::ActorVec objects;

        int k;
        detector.getDetectorPtr()->setColourSegDebug(true);

        bool move=false;

        ros::NodeHandle n;
        ros::ServiceClient client = n.serviceClient<robot_control::MoveToOS>("/gripperbot_control/move_to_os");
        robot_control::MoveToOS srv;

        double home_x=0.394137;
        double home_y=0.00033019;
        double home_z=0.363924;


        while(true)
        {

            detector.getDetectorPtr()->getOutputImg(detectImg);
            detector.getDetectorPtr()->getColourSegmentedImg(colorSegImg);

            imshow("detector",  detectImg);
            imshow("seg", colorSegImg);

            //std::cout << "Main loop" << std::endl;

            if(move)
            {
                mSub.getActorsData(objects);
                std::string type="BOX";
                std::string prop="YELLOW";
                int id=0;
                TargetPoseVec pose;

                std::cout << "Move " << std::endl;

                if(util::Util::getActorPose(objects, type, prop, id, pose))
                {
                    std::cout << "YELLOW BOX FOUND" << std::endl;

                    std::cout << pose[0] << std::endl;

                    double x,y,z;
                    x=(715.0-pose[0](0))/1000.0;
                    y=(300.0-pose[0](1))/1000.0;
                    z=210.0/1000.0;

                    std::cout << "x y z " << x << " " << y << " " << z << std::endl;

                    srv.request.x=home_x;
                    srv.request.y=home_y;
                    srv.request.z=home_z;
                    srv.request.effector="gripper";

                    if (client.call(srv))
                    {
                        if(srv.response.success)
                            std::cout << "Move successfull home" <<std::endl;
                        else
                            std::cout << "Move failed to home" <<std::endl;

                    }
                    else
                    {
                        ROS_ERROR("Failed to call service /robot_control/move_joints");

                    }

                    srv.request.x=x;
                    srv.request.y=y;
                    srv.request.z=z;
                    srv.request.effector="gripper";

                    if (client.call(srv))
                    {
                        if(srv.response.success)
                            std::cout << "Move successfull" <<std::endl;
                        else
                            std::cout << "Move failed to" <<std::endl;

                    }
                    else
                    {
                        ROS_ERROR("Failed to call service /robot_control/move_joints");
                    }

                    move=false;

                }
            }

            k = waitKey(100);

            if((int)(k & 0xFF) == 27)
                break;

            if((int)(k & 0xFF) == 'm')
                move=true;
        }

        detector.stopThread();

        detectImg.release();
        colorSegImg.release();

        mSub.stopThread();

        destroyWindow("detector");
        destroyWindow("seg");

        return 1;

    }
    catch (std::exception& e)
    {

        std::cout << e.what() << endl;
    }

    return 0;
};



