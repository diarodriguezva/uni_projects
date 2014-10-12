#include <QApplication>
#include <stdexcept>
#include <exception>
#include <signal.h>
#include <camera/ConfigData.h>
#include <camera/camInput/CamOpenCV.h>
#include <camera/main.h>
#include <comm_lib/ImagePublisher.h>
#include <comm_lib/ImageSubscriber.h>
using namespace std;
using namespace caminput;

int main(int argc, char** argv)
{
	
    try
    {
        ros::init(argc, argv, "camera");

        ConfigData config;
        config.parse();

        Cam* camin = new CamOpenCV(config.CAM_ID, config.CAMERA_INFO_SERVICE_NAME);

        cv::Mat img;

        comminterface::ImagePublisher imgPub(config.CAMERA_IMAGE_TOPIC_NAME);

        comminterface::ImageSubscriber imgSub(config.CAMERA_IMAGE_TOPIC_NAME);
        imgSub.start();

        int k;

        if(config.SHOW_DISPLAY)
        {
            cv::namedWindow("video", 1);
        }

        while(ros::ok())
        {
            camin->getImageCopy(img);
            imgPub.setImageData(img);

            if(config.SHOW_DISPLAY)
            {
                imgSub.getImageData(img);
                cv::imshow("video", img);
            }
            k = waitKey(20);
            if(k != -1)
                break;
        }

        if(config.SHOW_DISPLAY)
        {
            destroyWindow("video");
        }

        delete camin;

        return 1;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << endl;
    }

}




