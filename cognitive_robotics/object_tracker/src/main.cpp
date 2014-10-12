/*
* Tracking
* started by Suraj Nair
*/
#include <QApplication>

#include <stdexcept>
#include <exception>
#include <signal.h>
#include <opencv2/opencv.hpp>
#include "ros/ros.h"
#include "Tracker.h"

using namespace std;

int main(int argc, char** argv)
{
    try
    {
        ros::init(argc, argv, "object_tracker");

        cv::Mat img;

        tracking1::Tracker tracker;

        cv::namedWindow("tracker", 1);

        int k;

        while(true)
        {

            tracker.trackNext1();

            tracker.getOutputImage(img);

            cv::imshow("tracker", img);

            k = cv::waitKey(10);

            if((int)(k & 0xFF) == 27)
                break;

        }

        cv::destroyWindow("tracker");

        return 1;

    }
    catch (std::exception& e)
    {

        std::cout << e.what() << endl;
    }

    return 0;
};



