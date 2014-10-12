#include "comm_lib/DeviceStatusSubscriber.h"

namespace comminterface
{

RosDeviceStatusSubscriber::RosDeviceStatusSubscriber(const std::string& topicName)
{
    mTopicName = topicName;

    _sub = n.subscribe(topicName, 1000, &RosDeviceStatusSubscriber::deviceStatusCallback, this);

    runThread = true;

}

RosDeviceStatusSubscriber::~RosDeviceStatusSubscriber()
{
    std::cout << "Deleting Subscriber: " << mTopicName << std::endl;

    stopThread();

    while(!this->isFinished())
    {
        std::cout << "Waiting for thread to finish" << std::endl;
        QThread::msleep(100);
    }

    _sub.shutdown();

    std::cout << "Deleted Subscriber: " << mTopicName << std::endl;

}

void RosDeviceStatusSubscriber::deviceStatusCallback(const device_msgs::StatusConstPtr& data)
{
    this->setDeviceStatus(data);
}

void RosDeviceStatusSubscriber::setDeviceStatus(const device_msgs::StatusConstPtr& data)
{
    //std::cout << "Subscriber setDeviceStatus +++++++++++++++++++++++++++++++++++++++++ " << mTopicName << std::endl;
    mDeviceStatusMutex.lock();
    mDeviceStatus.deviceName = data->deviceName;
    mDeviceStatus.mode = data->mode;
    mDeviceStatus.action = data->action;
    mDeviceStatus.actionIdentifier = data->actionIdentifier;
    mDeviceStatus.result = data->result;
    mDeviceStatus.timeStamp = data->timeStamp;

//    std::cout << "mDeviceStatus.deviceName          " << mDeviceStatus.deviceName << std::endl;
//    std::cout << "mDeviceStatus.mode                " << mDeviceStatus.mode << std::endl;
//    std::cout << "mDeviceStatus.action              " << mDeviceStatus.action << std::endl;
//    std::cout << "mDeviceStatus.actionIdentifier    " << mDeviceStatus.actionIdentifier << std::endl;
//    std::cout << "mDeviceStatus.result              " << mDeviceStatus.result << std::endl;
//    std::cout << "mDeviceStatus.timeStamp           " << mDeviceStatus.timeStamp << std::endl;

    mDeviceStatusMutex.unlock();
}

void RosDeviceStatusSubscriber::getDeviceStatus(device_msgs::Status& data)
{
    //std::cout << "Subscriber getDeviceStatus ############################################### " << mTopicName << std::endl;
    mDeviceStatusMutex.lock();
    data.deviceName = mDeviceStatus.deviceName;
    data.mode = mDeviceStatus.mode;
    data.action = mDeviceStatus.action;
    data.actionIdentifier = mDeviceStatus.actionIdentifier;
    data.result = mDeviceStatus.result;
    data.timeStamp = mDeviceStatus.timeStamp;

//    std::cout << "data.deviceName          " << data.deviceName << std::endl;
//    std::cout << "data.mode                " << data.mode << std::endl;
//    std::cout << "data.action              " << data.action << std::endl;
//    std::cout << "data.actionIdentifier    " << data.actionIdentifier << std::endl;
//    std::cout << "data.result              " << data.result << std::endl;
//    std::cout << "data.timeStamp           " << data.timeStamp << std::endl;
    mDeviceStatusMutex.unlock();
}

void RosDeviceStatusSubscriber::run()
{
    std::cout << "Starting Ros Comm Subscriber: " << mTopicName << std::endl;

    //ros::spin();
    while (ros::ok() && runThread)
    {
        ros::getGlobalCallbackQueue()->callAvailable(ros::WallDuration(0.1));

        ros::spinOnce();

        //std::cout << "Running device status subscribers " << mTopicName << std::endl;
    }

}



}
