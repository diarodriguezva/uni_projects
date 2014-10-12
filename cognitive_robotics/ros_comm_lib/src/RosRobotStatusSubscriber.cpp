#include "RosRobotStatusSubscriber.h"

namespace comminterface
{

RosRobotStatusSubscriber::RosRobotStatusSubscriber(const std::string& topicName)
{
    mTopicName = topicName;

    ros::NodeHandle n;

    _sub = n.subscribe(topicName, 1000, &RosRobotStatusSubscriber::robotStatusCallback, this);

    runThread = true;
}

RosRobotStatusSubscriber::~RosRobotStatusSubscriber()
{
    std::cout << "Deleting Subscriber: " << mTopicName << std::endl;

    while(this->isRunning())
    {
        QThread::sleep(100);
    }

    this->wait();
}

void RosRobotStatusSubscriber::robotStatusCallback(const ros_tum_msgs::RobotStatusConstPtr& data)
{
    this->setRobotStatus(data);
}

void RosRobotStatusSubscriber::setRobotStatus(const ros_tum_msgs::RobotStatusConstPtr& data)
{
    mRobotStatusMutex.lock();
    mRobotStatus.mode = data->mode;
    mRobotStatus.action = data->action;
    mRobotStatus.actionIdentifier = data->actionIdentifier;
    mRobotStatus.timeStamp = data->timeStamp;
    mRobotStatusMutex.unlock();
}

void RosRobotStatusSubscriber::getRobotStatus(ros_tum_msgs::RobotStatus& data)
{
    mRobotStatusMutex.lock();
    data.mode = mRobotStatus.mode;
    data.action = mRobotStatus.action;
    data.actionIdentifier = mRobotStatus.actionIdentifier;
    data.timeStamp = mRobotStatus.timeStamp;
    mRobotStatusMutex.unlock();
}

void RosRobotStatusSubscriber::run()
{
    std::cout << "Starting Ros Comm Subscriber: " << mTopicName << std::endl;

    while (ros::ok() && runThread)
    {
        ros::getGlobalCallbackQueue()->callAvailable(ros::WallDuration(0.1));
    }

}



}
