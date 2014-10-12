#include <tf/transform_listener.h>
#include <QApplication>
#include <stdexcept>
#include <exception>
#include <signal.h>
#include "main.h"
#include <robot_control_srvs/MoveToCS.h>
#include <opencv2/opencv.hpp>

using namespace std;

/*Declaring the clients and message containers for the connection to cambot*/
ros::ServiceClient cambot_client;
robot_control_srvs::MoveToCS cambot_srv;

ros::ServiceClient gripperbot_client;
robot_control_srvs::MoveToCS gripperbot_srv;

void movegripperbot(float x, float y, float z)
{
    /*

      PUT YOUR CODE HERE
      Implement a function to move the gripperbot to position x,y,z (similar to movecambot)

    */

    /*creating the service request*/
    gripperbot_srv.request.x = x;
    gripperbot_srv.request.y = y;
    gripperbot_srv.request.z = z;
    gripperbot_srv.request.effector = "gripper";

    /*calling the move service*/
    if (gripperbot_client.call(gripperbot_srv))
    {
        /*checking for success of the move*/
        if(gripperbot_srv.response.success)
            std::cout << "Gripperbot Approach successfull " <<std::endl;
        else
            std::cout << "Gripperbot Approach failed to " << x << " " << y << " " << z << std::endl;
    }
    else
    {
        ROS_ERROR("Failed to call service /gripperbot_control/move_to_cs");
        throw;
    }
}
/*
    Moves the cambot to position x,y,z
    The service definitions have been defined in the robot_control_srvs/srv/MoveToCS.srv file
*/

void movecambot(float x, float y, float z)
{
    /*creating the service request*/
    cambot_srv.request.x=x;
    cambot_srv.request.y=y;
    cambot_srv.request.z=z;
    cambot_srv.request.effector="camera";

    /*calling the move service*/
    if (cambot_client.call(cambot_srv))
    {
        /*checking for success of the move*/
        if(cambot_srv.response.success)
            std::cout << "Approach successfull " <<std::endl;
        else
            std::cout << "Approach failed to " << x << " " << y << " " << z << std::endl;
    }
    else
    {
        ROS_ERROR("Failed to call service /cambot_control/move_to_cs");
        throw;
    }
}


/*
    Function to grasp an object located at position (x,y,z).
*/
void grasp(float &x, float &y, float &z)
{

    /*
        PUT YOUR CODE HERE!
        An example of the steps required:
        1. move to an approach pose (e.g. 5cm above the object)
        2. move down to the object
        3. move up to the approach pose

    */
    movegripperbot(x - 0.15, y, z);
    movegripperbot(x - 0.05, y, z);
}


void track(float &x, float &y, float &z)
{
    movegripperbot(x - 0.15, y, z);
}

int main(int argc, char** argv)
{
    try
    {
        ros::init(argc, argv, "demo_cogsys_viz_cpp");

        cv::Mat demoImg(480,640, CV_8UC3);
        cv::namedWindow("demo", 1);

        demoImg=cv::Scalar(0,0,0);

        cv::putText(demoImg, "Press ESC to quit app", cv::Point(30,30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,255,0), 1, CV_AA);
        cv::putText(demoImg, "Press g to grasp GREEN object", cv::Point(30,70), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,255,0), 1, CV_AA);
        cv::putText(demoImg, "Press t to track GREEN object", cv::Point(30,110), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,255,0), 1, CV_AA);

        int k;

        ros::NodeHandle n;

        /*creating the client for moving the cambot to a given cartesian pose*/
        cambot_client = n.serviceClient<robot_control_srvs::MoveToCS>("/cambot_control/move_to_cs");

        /*creating the client for moving the gripperbot to a given cartesian pose*/
        gripperbot_client = n.serviceClient<robot_control_srvs::MoveToCS>("/gripperbot_control/move_to_cs");

        /*move the cambot to the position, where the bag file was recorded from*/
        movecambot(0.215,0,0.4);

        tf::TransformListener listener;

        bool graspObject = false, trackObject = false;
        while(ros::ok())
        {

            std::string type="BOX";
            std::string prop="GREEN";
            int id=0;
            std::stringstream ss_object_name;
            ss_object_name << prop << "_" << type << "_" << id;

            tf::StampedTransform stamped_transform;
            try{
                /*
                      get the pose of the object w.r.t gripperbot_base frame
                    */
                listener.waitForTransform(ss_object_name.str(), "gripperbot_base",
                                          ros::Time(0), ros::Duration(1.0));
                listener.lookupTransform(ss_object_name.str(), "gripperbot_base",
                                         ros::Time(0), stamped_transform);
                float x,y,z;
                x = stamped_transform.getOrigin().getX();
                y = stamped_transform.getOrigin().getY();
                z = stamped_transform.getOrigin().getZ();
                /*checking for invalid/unreachable/noisy pose estimated from the camera*/
                if(z < 0) z = -z;
                if(x < 0) continue;
                /*
                      move the gripperbot using the obtained object position
                    */
                if(graspObject){
                    grasp(x,y,z);
                    graspObject=false;
                }
                if(trackObject)
                    track(x,y,z);
            }
            catch (tf::TransformException ex){
                std::cout << "NO " << prop  << " " << type << "found to grasp" << std::endl;
                ros::Duration(1.0).sleep();
            }

            imshow("demo",  demoImg);

            k = cv::waitKey(100);

            if((int)(k & 0xFF) == 27)
                break;

            if((int)(k & 0xFF) == 'g')
                graspObject = true;

            if((int)(k & 0xFF) == 't')
                trackObject = !trackObject;
        }

        demoImg.release();

        cv::destroyWindow("demoImg");

        cambot_client.shutdown();

        return 1;

    }
    catch (std::exception& e)
    {

        std::cout << e.what() << endl;
    }

    return 0;
};



