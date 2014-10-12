/*
 * RosGripperStatusPublisher.h
 *
 *  Created on: Jan 26, 2011
 *      Author: tracking
 */

#ifndef ROSGRIPPERSTATUSPUBLISHER_H_
#define ROSGRIPPERSTATUSPUBLISHER_H_

#include <QThread>
#include <QMutex>
#include <CommonDefs.h>
#include "ros_tum_msgs/GripperStatus.h"

using namespace std;


namespace comminterface
{

class RosGripperStatusPublisher : public QThread
{

public:

    RosGripperStatusPublisher(const std::string& topicName);

    virtual ~RosGripperStatusPublisher();

    virtual void run();

    void stop()
    {
        runThread = false;
    }

    void setGripperStatus(const ros_tum_msgs::GripperStatus& data);

    void getGripperStatus(ros_tum_msgs::GripperStatus& data);

    void setLoopRate(unsigned int rate);

public:

    bool runThread;

    unsigned int mLoopRate;

    ros_tum_msgs::GripperStatus mStatusData;
    QMutex  mStatusDataMutex;

    std::string mTopicName;

    ros::Publisher _pub;
};

};

#endif /*ICEROBOTSTATUSPUBLISHER_H_*/

