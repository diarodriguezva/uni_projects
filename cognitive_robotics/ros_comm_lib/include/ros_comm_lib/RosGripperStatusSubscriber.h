/*
 * RosGripperStatusSubscriber.h
 *
 *  Created on: Jan 26, 2011
 *      Author: tracking
 */

#ifndef ROSGRIPPERSTATUSSUBSCRIBER_H_
#define ROSGRIPPERSTATUSSUBSCRIBER_H_

#include <ros_comm_lib/CommonDefs.h>
#include "ros_tum_msgs/GripperStatus.h"
#include "ros_tum_msgs/GripperMode.h"
#include <sstream>

using namespace std;

namespace comminterface
{

class RosGripperStatusSubscriber : public QThread
{

public:

    RosGripperStatusSubscriber(const std::string& topicName);

    virtual ~RosGripperStatusSubscriber();

    virtual void run();

    void stop()
    {
        runThread = false;
    }


    void gripperStatusCallback(const ros_tum_msgs::GripperStatusConstPtr& data)
    {
        this->setGripperStatus(data);
    }

    void setGripperStatus(const ros_tum_msgs::GripperStatusConstPtr& data);

    void getGripperStatus(ros_tum_msgs::GripperStatus& data);

public:

    bool runThread;

    std::string mTopicName;

    ros_tum_msgs::GripperStatus mGripperStatus;
    QMutex  mGripperStatusDataMutex;

    ros::Subscriber _sub;

};

};

#endif /*ROSGRIPPERSTATUSSUBSCRIBER_H_*/

