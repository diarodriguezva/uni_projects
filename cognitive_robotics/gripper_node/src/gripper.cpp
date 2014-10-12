#include <ros/ros.h>
#include <dummy_robot_control/PrintPose.h>
#include <dummy_robot_control/MoveJoints.h>
#include <world/found_objects.h>
#include <std_msgs/String.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gripper");
  ros::NodeHandle n;
  ros::ServiceClient foundball = n.serviceClient<world::found_objects>("/world/found_objects");
       world::found_objects srv1;
       if (foundball.call(srv1))
       {
           std::cout<<srv1::name;
       }
       else
       {
           ROS_ERROR("Failed to find ball");
           return 1;
       }
  ros::ServiceClient movegripper = n.serviceClient<dummy_robot_control::MoveJoints>("/gripperbot_control/move_joints");
       dummy_robot_control::MoveJoints srv2;
       srv2.request.q0 = 0.4;
       srv2.request.q1 = 0.2;
       srv2.request.q2 = 0.4;
   if (movegripper.call(srv2))
     {
       ROS_INFO("Move successfully to");
     }
     else
     {
       ROS_ERROR("Failed to move gripper");
       return 1;
     }

  return 0;
}
