/*
 * RosRobotStatusPublisher.h
 *
 *  Created on: Jan 26, 2011
 *      Author: tracking
 */

#ifndef ROSROBOTSTATUSPUBLISHER_H_
#define ROSROBOTSTATUSPUBLISHER_H_

#include <QThread>
#include <QMutex>
#include <ros_comm_lib/CommonDefs.h>
#include "ros_tum_msgs/RobotStatus.h"

using namespace std;


namespace comminterface
{

class RosRobotStatusPublisher : public QThread
{

public:

    RosRobotStatusPublisher(const std::string& topicName);

    virtual ~RosRobotStatusPublisher();

    virtual void run();

    void stop()
    {
        runThread = false;
    }

    void setRobotStatus(const ros_tum_msgs::RobotStatus& data);

    void getRobotStatus(ros_tum_msgs::RobotStatus& data);

    void setLoopRate(unsigned int rate);

public:

    bool runThread;

    unsigned int mLoopRate;

    ros_tum_msgs::RobotStatus mStatusData;
    QMutex  mStatusDataMutex;

    std::string mTopicName;

    ros::Publisher _pub;
};

};

#endif /*ROSROBOTSTATUSPUBLISHER_H_*/

