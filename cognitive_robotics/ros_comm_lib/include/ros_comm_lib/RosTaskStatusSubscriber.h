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

#ifndef ROSTASKSTATUSSUBSCRIBER_H_
#define ROSTASKSTATUSSUBSCRIBER_H_

#include <ros_comm_lib/CommonDefs.h>
#include "ros_tum_msgs/TaskStatusVec.h"

using namespace std;

namespace comminterface
{

/**
 * @brief Class for ROS Task Status Subscriber
 * @author Suraj Nair nair@fortiss.org, nair@in.tum.de
 */
class RosTaskStatusSubscriber : public QThread
{

public:

    /**
     * @brief Default Constructor
     *
     * @param topicName Name of Topic to subscribe
     */
    RosTaskStatusSubscriber(const std::string& topicName);

    /**
     * @brief Destructor
     *
     */
    virtual ~RosTaskStatusSubscriber();

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
     * @param data Task Status Data Container
     */
    void taskStatusCallback(const ros_tum_msgs::TaskStatusVecConstPtr& data);

    /**
     * @brief Method to set Task Status Data
     *
     * @param data Task Status Container
     */
    void setTaskStatus(const ros_tum_msgs::TaskStatusVecConstPtr& data);

    /**
     * @brief Method to get Task Status Data
     *
     * @param data Task Status Container
     */
    void getTaskStatus(ros_tum_msgs::TaskStatusVec& data);

public:

    bool runThread; /**< Thread Run Flag */

    std::string mTopicName; /**< Topic Name */

    ros_tum_msgs::TaskStatusVec mTaskStatus; /**< Task Status Data Container */
    QMutex  mStatusMutex; /**< Task Status Data Mutex */

    ros::Subscriber _sub; /**< ROS Subscriber */


};

};

#endif /*ROSTASKSTATUSSUBSCRIBER_H_*/

