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

#ifndef ROSTASKSTATUSPUBLISHER_H_
#define ROSTASKSTATUSPUBLISHER_H_

#include <QThread>
#include <QMutex>
#include <ros_comm_lib/CommonDefs.h>
#include "ros_tum_msgs/TaskStatusVec.h"

using namespace std;

namespace comminterface
{

/**
 * @brief Class for ROS Task Status (Robot/Gripper etc.) Publisher
 * @author Suraj Nair nair@fortiss.org, nair@in.tum.de
 */
class RosTaskStatusPublisher : public QThread
{

public:

    /**
     * @brief Default Constructor
     *
     * @param topicName Name of Topic to be published
     */
    RosTaskStatusPublisher(const std::string& topicName);

    /**
     * @brief Destructor
     *
     */
    virtual ~RosTaskStatusPublisher();

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
     * @brief Method to set Task Status Data
     *
     * @param data Task Status Container
     */
    void setTaskStatus(const ros_tum_msgs::TaskStatusVec& data);

    /**
     * @brief Method to get Task Status Data
     *
     * @param data Task Status Container
     */
    void getTaskStatus(ros_tum_msgs::TaskStatusVec& data);

    /**
     * @brief Method to set thread loop rate
     *
     * @param rate Loop rate (msecs)
     */
    void setLoopRate(unsigned int rate);

public:

    bool runThread; /**< Thread Run Flag */

    unsigned int mLoopRate; /**< Thread Loop Rate  */

    std::string mTopicName; /**< TODO */

    ros_tum_msgs::TaskStatusVec mStatusData; /**< Task Status Data Container  */
    QMutex  mStatusDataMutex; /**< Task Status Data Mutex  */

    ros::Publisher _pub; /**< ROS Publisher  */


};

};

#endif /*RosTaskStatusPublisher*/

