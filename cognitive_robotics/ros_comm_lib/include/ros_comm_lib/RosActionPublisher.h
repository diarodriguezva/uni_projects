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


#ifndef ROSACTIONPUBLISHER_H_
#define ROSACTIONPUBLISHER_H_

#include <QThread>
#include <QMutex>
#include <ros_comm_lib/CommonDefs.h>
#include "ros_tum_msgs/ActionVec.h"
#include <ros_comm_lib/util/Util.h>

using namespace std;
using namespace util;

namespace comminterface
{

/**
 * @brief Class for ROS Action Publisher
 * @author Suraj Nair nair@fortiss.org, nair@in.tum.de
 */
class RosActionPublisher : public QThread
{

public:

/**
 * @brief Default Constructor
 *
 * @param topicName Name of Topic to be published
 */
    RosActionPublisher(const std::string& topicName);

    /**
     * @brief Destructor
     *
     */
    virtual ~RosActionPublisher();

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
     * @brief Method to set thread loop rate
     *
     * @param rate Loop rate (msecs)
     */
    void setLoopRate(unsigned int rate);

    /**
     * @brief Method to Set Action Data
     *
     * @param data Action Data Vector
     */
    void setActionData(const ros_tum_msgs::ActionVec& data);

    /**
     * @brief Method to get Action Data
     *
     * @param data Action Data Vector
     */
    void getActionData(ros_tum_msgs::ActionVec& data);

private:

    bool runThread; /**< Thread Run Flag */

    unsigned int mLoopRate; /**< Thread Loop Rate */

    std::string mTopicName; /**< Topic Name Published */

    ros_tum_msgs::ActionVec mActionData; /**< Action Data Container */
    QMutex  mActionDataMutex; /**< Action Data Mutex */

    ros::Publisher _pub; /**< ROS Publisher */
};

};

#endif /*ROSACTIONPUBLISHER_H_*/

