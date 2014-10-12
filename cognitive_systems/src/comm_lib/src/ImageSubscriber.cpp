#include "comm_lib/ImageSubscriber.h"


namespace comminterface
{

ImageSubscriber::ImageSubscriber(const std::string& topicName)
    : it_(nh_)
{
    mTopicName = topicName;

    image_sub_ = it_.subscribe(topicName.c_str(), 1, &ImageSubscriber::imageCallback, this);

    mImg=cv::Mat(480,640,CV_8UC3);

    runThread = true;
}

ImageSubscriber::~ImageSubscriber()
{
    std::cout << "Deleting Subscriber " << mTopicName << std::endl;

    stopThread();

    while(!this->isFinished())
    {
        std::cout << "Waiting for thread to finish" << std::endl;
        QThread::msleep(100);
    }

    mImg.release();
    image_sub_.shutdown();

    std::cout << "Deleted Subscriber " << mTopicName << std::endl;

}

void ImageSubscriber::imageCallback(const sensor_msgs::ImageConstPtr& data)
{
    //std::cout << "imageCallback" << std::endl;
    this->setImageData(data);
}

void ImageSubscriber::setImageData(const sensor_msgs::ImageConstPtr& data)
{
    //std::cout << "setImageData " << std::endl;
    mImageDataMutex.lock();

    //std::cout << "size subscriber " << data->width << " " << data->height << std::endl;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(data, sensor_msgs::image_encodings::BGR8);
        mImg=cv_ptr->image;
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        throw;
    }
    mNewImage=true;
    mImageDataMutex.unlock();
    //std::cout << "setImageData done " << std::endl;
}

bool ImageSubscriber::getImageData(cv::Mat& data)
{
    //std::cout << "getImageData" << std::endl;
    bool imageFound=false;
    mImageDataMutex.lock();
    if(mNewImage)
    {
        data=mImg;
        mNewImage=false;
        imageFound=true;
    }
    mImageDataMutex.unlock();

    return imageFound;
    //std::cout << "getImageData done " << std::endl;
}

void ImageSubscriber::run()
{
    std::cout << "Starting Ros Comm Subscriber: " << mTopicName << std::endl;

    while (ros::ok() && runThread)
    {
        ros::getGlobalCallbackQueue()->callAvailable(ros::WallDuration(0.02));
        //std::cout << "Running " << std::endl;
    }
}

}
