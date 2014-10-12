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


#ifndef IMAGEPUBLISHER_H_
#define IMAGEPUBLISHER_H_

#include <QMutex>
#include <comm_lib/CommonDefs.h>
#include <comm_lib/util/Util.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace util;

namespace comminterface
{

/**
 * @brief Class for ROS Actors Publisher
 * @author Suraj Nair nair@fortiss.org, nair@in.tum.de
 */
class ImagePublisher
{

public:

    /**
     * @brief Default Constructor
     *
     * @param topicName Name of Topic to be published
     */
    ImagePublisher(const std::string& topicName);

    /**
     * @brief Destructor
     *
     */
    virtual ~ImagePublisher();

    /**
     * @brief Method to set Cam Info Data
     *
     * @param width Camera image width
     * @param height Camera image height
     * @param intr_data Intrinsics data Matrix
     * @param extr_data Extrinsics data Matrix
     */
    void setCamInfoData(int width, int height, cv::Mat& intr_data,cv::Mat& extr_data);


    /**
     * @brief Method to set Image Data
     *
     * @param data Image Container
     */
    void setImageData(cv::Mat& data);

    /**
     * @brief Method to get Image data
     *
     * @param data Image Container
     */
    void getImageData(sensor_msgs::Image& data);


public:

    std::string mTopicName; /**< Topic Name Published */

    QMutex mImageDataMutex; /**< Image Data Mutex  */
    sensor_msgs::Image mImageData; /**< Image Data Container  */
    cv_bridge::CvImage cv_b; /**< Image Bridge*/
    sensor_msgs::CameraInfo mCamInfo;

    ros::NodeHandle nh_; /**< Ros Node  */
    image_transport::ImageTransport it_; /**< Image Transporter  */
    image_transport::Publisher image_pub_; /**< Image Subscriber  */

};

};

#endif /*IMAGEPUBLISHER_H_*/

