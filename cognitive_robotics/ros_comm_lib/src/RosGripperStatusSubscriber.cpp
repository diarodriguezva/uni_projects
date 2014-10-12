#include "RosGripperStatusSubscriber.h"

namespace comminterface
{

RosGripperStatusSubscriber::RosGripperStatusSubscriber(const std::string& topicName)
{
    mTopicName = topicName;

    ros::NodeHandle n;

    _sub = n.subscribe(topicName, 1000, &RosGripperStatusSubscriber::gripperStatusCallback, this);

    runThread = true;
}

RosGripperStatusSubscriber::~RosGripperStatusSubscriber()
{
    std::cout << "Deleting Subscriber: " << mTopicName << std::endl;

    while(this->isRunning())
    {
        QThread::sleep(100);
    }

    this->wait();

}

void RosGripperStatusSubscriber::setGripperStatus(const ros_tum_msgs::GripperStatusConstPtr& data)
{
    mGripperStatusDataMutex.lock();
    mGripperStatus.mode = data->mode;
    mGripperStatus.actionName = data->actionName;
    mGripperStatus.actionIdentifier = data->actionIdentifier;
    mGripperStatus.timeStamp = data->timeStamp;
    mGripperStatusDataMutex.unlock();
}

void RosGripperStatusSubscriber::getGripperStatus(ros_tum_msgs::GripperStatus& data)
{
    mGripperStatusDataMutex.lock();
    data.mode = mGripperStatus.mode;
    data.actionName = mGripperStatus.actionName;
    data.actionIdentifier = mGripperStatus.actionIdentifier;
    data.timeStamp = mGripperStatus.timeStamp;
    mGripperStatusDataMutex.unlock();
}


void RosGripperStatusSubscriber::run()
{

    std::cout << "Starting Ros Comm Subscriber: " << mTopicName << std::endl;

    while (ros::ok() && runThread)
    {
        ros::getGlobalCallbackQueue()->callAvailable(ros::WallDuration(0.1));
    }

}

}
