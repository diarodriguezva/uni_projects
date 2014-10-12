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


#ifndef ROSACTIONSUBSCRIBER_H_
#define ROSACTIONSUBSCRIBER_H_

#include <ros_comm_lib/CommonDefs.h>
#include <QMutex>
#include <ros_tum_msgs/ActionVec.h>
#include <sstream>
#include <ros_comm_lib/util/Util.h>

using namespace std;
using namespace util;

namespace comminterface
{
/**
 * @brief Class for ROS Action Subscriber
 * @author Suraj Nair nair@fortiss.org, nair@in.tum.de
 */
class RosActionSubscriber : public QThread
{

public:

    /**
     * @brief Default Constructor
     *
     * @param topicName Name of Topic to subscribe
     */
    RosActionSubscriber(const std::string& topicName);

    /**
     * @brief Destructor
     *
     */
    virtual ~RosActionSubscriber();

    /**
     * @brief Method to stop thread run
     *
     */
    void stopThread()
    {
        runThread = false;
    }

    /**
     * @brief Thread run
     *
     */
    virtual void run();

    /**
     * @brief Method For ROS Callbak Function
     *
     * @param data Action Container
     */
    void actionCallback(const ros_tum_msgs::ActionVecPtr& data);

    /**
     * @brief Method to Set Action Data
     *
     * @param data Action Container
     */
    void setActionData(const ros_tum_msgs::ActionVecPtr& data);

    /**
     * @brief Method to get Action Data
     *
     * @param data Action Container
     */
    void getActionData(ros_tum_msgs::ActionVec& data);

public:

    bool runThread; /**< Thread Run Flag  */

    std::string mTopicName; /**< Topic Name */

    ros_tum_msgs::ActionVec mActionData; /**< Action Data Container  */
    QMutex  mActionDataMutex; /**< Action Data Mutex */

    ros::Subscriber _sub; /**< ROS Subscriber */

};

};

#endif /*ROSACTIONSUBSCRIBER_H_*/

