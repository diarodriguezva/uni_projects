/*
* Tracking
* started by Suraj Nair
*/
#include <QApplication>
#include <stdexcept>
#include <exception>
#include <signal.h>
#include <ConfigData.h>
#include <camInput/CamOpenCV.h>
#include "main.h"
#include <ros_comm_lib/RosImagePublisher.h>
#include <ros_comm_lib/RosImageSubscriber.h>
using namespace std;
using namespace caminput;

int main(int argc, char** argv)
{
    try
    {
        ros::init(argc, argv, "camera_0");

        ConfigData config;
        config.parse();

        Cam* camin = new CamOpenCV(config.CAM_ID, config.CAMERA_INFO_SERVICE_NAME);

        cv::Mat img;
        cv::Mat img1(480, 640, CV_8UC3);

        comminterface::RosImagePublisher imgPub(config.CAMERA_IMAGE_TOPIC_NAME);
        //imgPub.start();

        comminterface::RosImageSubscriber imgSub(config.CAMERA_IMAGE_TOPIC_NAME);
        imgSub.start();

        int k;

        if(config.SHOW_DISPLAY)
        {
            cv::namedWindow("cam", 1);
        }

        while(true)
        {

            camin->getImageCopy(img);
            imgPub.setImageData(img);

            //std::cout << __LINE__ << std::endl;

            if(config.SHOW_DISPLAY)
            {
                imgSub.getImageData(img1);
                cv::imshow("cam", img1);
            }
            k = waitKey(1);

            if((int)(k & 0xFF) == 27)
                break;

        }


        if(config.SHOW_DISPLAY)
        {
            destroyWindow("cam");
        }

        delete camin;

        return 1;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << endl;
    }

}




