/*
 * RosRobotStatusSubscriber.h
 *
 *  Created on: Jan 26, 2011
 *      Author: tracking
 */

#ifndef ROSROBOTSTATUSSUBSCRIBER_H_
#define ROSROBOTSTATUSSUBSCRIBER_H_

#include <ros_comm_lib/CommonDefs.h>
#include "ros_tum_msgs/RobotStatus.h"
#include "ros_tum_msgs/RobotMode.h"
#include <sstream>

using namespace std;

namespace comminterface
{

class RosRobotStatusSubscriber : public QThread
{

public:

    RosRobotStatusSubscriber(const std::string& topicName);

    virtual ~RosRobotStatusSubscriber();

    virtual void run();

    void stop()
    {
        runThread = false;
    }

    void robotStatusCallback(const ros_tum_msgs::RobotStatusConstPtr& data);

    void setRobotStatus(const ros_tum_msgs::RobotStatusConstPtr& data);

    void getRobotStatus(ros_tum_msgs::RobotStatus& data);

public:

    bool runThread;

    std::string mTopicName;

    ros_tum_msgs::RobotStatus mRobotStatus;
    QMutex  mRobotStatusMutex;

    ros::Subscriber _sub;

};

};

#endif /*ROSROBOTSTATUSSUBSCRIBER_H_*/

