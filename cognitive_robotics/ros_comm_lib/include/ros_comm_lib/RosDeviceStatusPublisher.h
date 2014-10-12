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


#ifndef ROSDEVICESTATUSPUBLISHER_H_
#define ROSDEVICESTATUSPUBLISHER_H_

#include <QThread>
#include <QMutex>
#include <ros_comm_lib/CommonDefs.h>
#include "ros_tum_msgs/DeviceStatus.h"

using namespace std;


namespace comminterface
{


/**
 * @brief Class for ROS Device Status (Robot/Gripper etc.) Publisher
 * @author Suraj Nair nair@fortiss.org, nair@in.tum.de
 */
class RosDeviceStatusPublisher : public QThread
{

public:

    /**
     * @brief Default Constructor
     *
     * @param topicName Name of Topic to be published
     */
    RosDeviceStatusPublisher(const std::string& topicName);

    /**
     * @brief Destructor
     *
     */
    virtual ~RosDeviceStatusPublisher();

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
     * @brief Method to set Device Status Data
     *
     * @param data Device Status Container
     */
    void setDeviceStatus(const ros_tum_msgs::DeviceStatus& data);

    /**
     * @brief Method to get Device Status Data
     *
     * @param data Device Status Container
     */
    void getDeviceStatus(ros_tum_msgs::DeviceStatus& data);

    /**
     * @brief Method to set thread loop rate
     *
     * @param rate Loop rate (msecs)
     */
    void setLoopRate(unsigned int rate);

public:

    bool runThread; /**< Thread Run Flag */

    unsigned int mLoopRate; /**< Thread Loop Rate  */

    ros_tum_msgs::DeviceStatus mStatusData; /**< Device Status Data Container  */
    QMutex  mStatusDataMutex; /**< Device Status Data Mutex  */

    std::string mTopicName; /**< Topic Name Published */

    ros::NodeHandle n; /**< ROS Node */

    ros::Publisher _pub; /**< ROS Publisher */
};

};

#endif /*ROSDEVICESTATUSPUBLISHER_H_*/

