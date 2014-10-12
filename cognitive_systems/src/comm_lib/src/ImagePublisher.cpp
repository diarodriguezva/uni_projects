#include "comm_lib/ImagePublisher.h"

namespace comminterface
{

ImagePublisher::ImagePublisher(const std::string& topicName)
    : it_(nh_)
{
    mTopicName = topicName;

    image_pub_ = it_.advertise(topicName.c_str(), 1);

    cv::Mat tmpImage(480, 640, CV_8UC3);
    cv_b.image=tmpImage;

}

ImagePublisher::~ImagePublisher()
{
    std::cout << "Deleting Publisher: " << mTopicName << std::endl;

    image_pub_.shutdown();

    std::cout << "Deleted Publisher: " << mTopicName << std::endl;
}

void ImagePublisher::setCamInfoData(int width, int height, cv::Mat& intr_data,cv::Mat& extr_data)
{
    //std::cout << "setCamInfoData" << std::endl;

    mCamInfo.width=width;
    mCamInfo.height=height;

    for(int i=0;i<9;++i)
    {
        mCamInfo.K[i]=intr_data.data [i];
    }

    //std::cout << "setCamInfoData done" << std::endl;
}

void ImagePublisher::setImageData(cv::Mat& data)
{
    //std::cout << "publisher set data " << std::endl;
    //std::cout << "data size " << data.ActorVec.size() << std::endl;

    mImageDataMutex.lock();
    ros::Time time = ros::Time::now();
    cv_b.header.stamp = time;
    cv_b.header.frame_id = "image";
    cv_b.encoding = "bgr8";
    cv_b.image=data;
    image_pub_.publish(cv_b.toImageMsg());

    mImageDataMutex.unlock();


    //std::cout << "#########################################################################################################" << std::endl;
}



}
