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
#include <comm_lib/ActorsSubscriber.h>
#include <comm_lib/util/Util.h>
#include <comm_lib/CommonDefs.h>

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

        int k;
        detector.getDetectorPtr()->setColourSegDebug(true);


        while(ros::ok())
        {

            detector.getDetectorPtr()->getOutputImg(detectImg);
            detector.getDetectorPtr()->getColourSegmentedImg(colorSegImg);

            imshow("detector",  detectImg);
            imshow("seg", colorSegImg);

            //std::cout << "Main loop" << std::endl;

            k = waitKey(100);

            if((int)(k & 0xFF) == 27)
                break;
        }

        detector.stopThread();

        detectImg.release();
        colorSegImg.release();

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



