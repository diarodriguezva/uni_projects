/*
     Written by: Christoph Klopf
 */

#include <ros/ros.h>
#include "std_msgs/String.h"

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
#include "cmac.h"


void listen(const BILHR_ros::LegPosition::ConstPtr& legPos)
{
    cout << "LegPosition:" << (int)legPos->LegPos << endl;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "move_leg");
    ros::NodeHandle move_leg_handle;

    ros::Subscriber sub = move_leg_handle.subscribe("leg_state",1,listen);

    ros::spin();

    return 0;
}
