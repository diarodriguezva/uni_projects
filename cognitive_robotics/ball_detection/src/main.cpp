#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <map>
#include <std_msgs/String.h>
#include <cxcore.h>

#include <ball_detection/find_boxes.h>
#include <ball_detection/find_balls.h>
#include "trackable.h"

// Measures
#define DIAMETER_BALL 70 //mm
#define NUMBER_BALLS 3
#define CAM_EFFECTOR_1 0.09
#define CAM_EFFECTOR_2 0.03

using namespace cv;
using namespace std;

//Store all constants for image encodings in the enc namespace to be used later.
namespace enc = sensor_msgs::image_encodings;

//Use method of ImageTransport to create image publisher
image_transport::Publisher pub;

map<std::string,Trackable*> balls;
//typedef std::map<std::string, Trackable*> iterator it_type;

Mat img_bgr, img_hsv;

Trackable* test;

//This function is called everytime a new image is published
void imageCallback(const sensor_msgs::ImageConstPtr& original_image)
{

    //#########################################
    //##### Aquire Image from Message #####
    //Convert from the ROS image message to a CvImage suitable for working with OpenCV for processing
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        //Always copy, returning a mutable CvImage
        //OpenCV expects color images to use BGR channel order.
        cv_ptr = cv_bridge::toCvCopy(original_image, enc::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        //if there is an error during conversion, display it
        ROS_ERROR("tutorialROSOpenCV::main.cpp::cv_bridge exception: %s", e.what());
        return;
    }
    img_bgr = cv_ptr->image.clone();
    //##### END Aquire Image from Message #####
    //#########################################

    // Convert to HSV Space to recognize the colors
    cvtColor(img_bgr,img_hsv,CV_BGR2HSV);

    static tf::TransformBroadcaster br;
    tf::Transform transform;

    tf::Quaternion q;
    q.setRPY(0,0,0);
    transform.setRotation(q);

    for (map<std::string,Trackable*>::const_iterator iter = balls.begin(); iter!=balls.end(); ++iter){

        if(iter->first == "red"){
            ((Trackable*)balls[iter->first])->findBalls(img_hsv,img_bgr);
        }

        //balls[iter->first]->drawOnto(img_bgr);
        Vec3f pos3D = balls[iter->first]->get3Dcoordinates();
        balls[iter->first]->drawBalls(img_bgr);

        // Convert in m
        for (int i=0;i<3;i++){
            pos3D[i] = pos3D[i]/1000;
        }

        if(iter->first == "green"){
            cout << "Green Ball --- x: " << pos3D[0] <<" y: " << pos3D[1] << " z: " << pos3D[2] << endl;
        }
        if(iter->first == "red"){
            cout << "Red Ball --- x: " << pos3D[0] <<" y: " << pos3D[1] << " z: " << pos3D[2] << endl;
        }
        if(iter->first == "yellow"){
            cout << "Yellow Ball --- x: " << pos3D[0] <<" y: " << pos3D[1] << " z: " << pos3D[2] << endl;
            cout << "------------" << endl;
        }

        transform.setOrigin(tf::Vector3(pos3D[0]+CAM_EFFECTOR_2,pos3D[1],pos3D[2]+CAM_EFFECTOR_1));
        br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"cam_effector","tf_" + iter->first + "_start"));
    }

    //Display the image using OpenCV
    imshow("Image Processed", img_bgr);
    //imshow("Green Blobs", balls["green"]->getMask(img_hsv));
    //imshow("Red Blobs", balls["red"]->getMask(img_hsv));
    //imshow("Yellow Blobs", balls["yellow"]->getMask(img_hsv));

    //Add some delay in miliseconds. The function only works if there is at least one HighGUI window created and the window is active. If there are several HighGUI windows, any of them can be active.
    waitKey(3);

    //Convert the CvImage to a ROS image message and publish it on the "camera/image_processed" topic.
    pub.publish(cv_ptr->toImageMsg());
}

bool serviceCallbackFindBoxes(ball_detection::find_boxes::Request &req,
                              ball_detection::find_boxes::Response &res)
{
    int* corners;
    int i = 0;

    for (map<std::string,Trackable*>::const_iterator iter = balls.begin(); iter!=balls.end(); ++iter){
        corners = balls[iter->first]->findBoxes(img_hsv, img_bgr);

        res.x_min[i] = corners[0];
        res.x_max[i] = corners[1];
        res.y_max[i] = corners[2];
        res.y_min[i] = corners[3];
        res.color[i] = iter->first;
        i++;
    }
    return true;
}

bool serviceCallbackFindBalls(ball_detection::find_balls::Request &req,
                              ball_detection::find_balls::Response &res)
{
    Vec2f pos2D;
    int i = 0;

    for (map<std::string,Trackable*>::const_iterator iter = balls.begin(); iter!=balls.end(); ++iter){
        ((Trackable*)balls[iter->first])->findBalls(img_hsv,img_bgr);
        pos2D = balls[iter->first]->get2Dcoordinates();

        res.x[i] = pos2D[0];
        res.y[i] = pos2D[1];
        res.name[i] = iter->first;
        i++;
    }
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_processor");
    ros::NodeHandle nh;
    //Create an ImageTransport instance, initializing it with our NodeHandle.
    image_transport::ImageTransport it(nh);

    //define possible objects
    test = new Trackable(Scalar(45,70,70),Scalar(90,210,150),DIAMETER_BALL,"green");
    balls["green"] = test;
    test = new Trackable(Scalar(165,50,50),Scalar(10,255,255),DIAMETER_BALL,"red");
//    test = new Trackable(Scalar(240,50,50),Scalar(10,255,165),DIAMETER_BALL,"red");
    balls["red"] = test;
    test = new Trackable(Scalar(20,150,120),Scalar(40,255,255),DIAMETER_BALL,"yellow");
    balls["yellow"] = test;

    image_transport::Subscriber sub = it.subscribe("gscam/image_raw", 1, imageCallback);
    //image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);

    pub = it.advertise("camera/image_processed", 1);

    std::stringstream ss1;
    std::stringstream ss2;
    ss1 << "/ball_detection/find_boxes";
    ss2 << "/ball_detection/find_balls";

    ros::ServiceServer service_list = nh.advertiseService(ss1.str(), serviceCallbackFindBoxes);
    ros::ServiceServer service_list2 = nh.advertiseService(ss2.str(), serviceCallbackFindBalls);

    ros::spin();
}
