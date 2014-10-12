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


#ifndef ROSDEVICESTATUSSUBSCRIBER_H_
#define ROSDEVICESTATUSSUBSCRIBER_H_

#include <comm_lib/CommonDefs.h>
#include <device_msgs/Status.h>
#include <device_msgs/Mode.h>
#include <sstream>

using namespace std;

namespace comminterface
{

/**
 * @brief Class for ROS Device Status Subscriber
 * @author Suraj Nair nair@fortiss.org, nair@in.tum.de
 */
class RosDeviceStatusSubscriber : public QThread
{

public:

    /**
     * @brief Default Constructor
     *
     * @param topicName Name of Topic to subscribe
     */
    RosDeviceStatusSubscriber(const std::string& topicName);

    /**
     * @brief Destructor
     *
     */
    virtual ~RosDeviceStatusSubscriber();

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
     * @param data Device Status Data Container
     */
    void deviceStatusCallback(const device_msgs::StatusConstPtr& data);

    /**
     * @brief Method to set Device Status Data
     *
     * @param data Device Status Container
     */
    void setDeviceStatus(const device_msgs::StatusConstPtr& data);

    /**
     * @brief Method to get Device Status Data
     *
     * @param data Device Status Container
     */
    void getDeviceStatus(device_msgs::Status& data);

public:

    bool runThread; /**< Thread Run Flag  */

    std::string mTopicName; /**< Topic Name */

    device_msgs::Status mDeviceStatus; /**< Device Status Data Container */
    QMutex  mDeviceStatusMutex; /**< Device Status Data Mutex */

    ros::NodeHandle n; /**< ROS Node */
    ros::Subscriber _sub; /**< ROS Subscriber */

};

};

#endif /*ROSDEVICESTATUSSUBSCRIBER_H_*/

