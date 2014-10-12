/** BEGIN LICENCE ************************************************************/
/* Copyright 2011-2012 TUM-fortiss                    		             */
/* All Rights Reserved.                                                      */
/* Contact author: Suraj Nair                                                */
/* E-mail: nair@fortiss.org, nair@in.tum.de	                             */
/* If you have any questions regarding this agreement or the licensing of    */
/* this technology, please send them to the contact author above.            */
/*                                                                           */
/* Author(s):                                                                */
/* Suraj Nair nair@fortiss.org, nair@in.tum.de	                             */
/** END LICENCE **************************************************************/


#ifndef IMAGESUBSCRIBER_H_
#define IMAGESUBSCRIBER_H_

#include "CommonDefs.h"
#include <sstream>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

namespace comminterface
{
/**
 * @brief Class for ROS Image Subscriber
 * @author Suraj Nair nair@fortiss.org, nair@in.tum.de
 */
class ImageSubscriber : public QThread
{

public:

    /**
     * @brief Default Constructor
     *
     * @param topicName Name of Topic to subscribe
     */
    ImageSubscriber(const std::string& topicName);

    /**
     * @brief Destructor
     *
     */
    virtual ~ImageSubscriber();

    /**
     * @brief Thread run
     *
     */
    virtual void run();

    /**
     * @brief Method to stop thread run
     *
     */
    void stopThread()
    {
        runThread = false;
    }


    /**
     * @brief Method For ROS Callbak Function
     *
     * @param data Actors Container
     */
    void imageCallback(const sensor_msgs::ImageConstPtr& data);

    /**
     * @brief Method to set Actors Data
     *
     * @param data Actors Container
     */
    void setImageData(const sensor_msgs::ImageConstPtr& data);

    /**
     * @brief Method to get Actors Data
     *
     * @param data Actors Container
     */
    bool getImageData(cv::Mat& data);

public:

    bool runThread; /**< Thread Run Flag  */

    std::string mTopicName; /**< Topic Name */

    QMutex mImageDataMutex; /**< Image Data Mutex */
    cv_bridge::CvImagePtr cv_ptr;/**< Image Bridge*/
    cv::Mat mImg; /**< Image Container  */
    bool mNewImage; /**< Flag indicating new image */

    ros::NodeHandle nh_; /**< Ros Node  */
    image_transport::ImageTransport it_; /**< Image Transporter  */
    image_transport::Subscriber image_sub_; /**< Image Subscriber  */
};
};

#endif /*ROSIMAGESUBSCRIBER_H_*/

