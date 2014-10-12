#include "comm_lib/DeviceStatusPublisher.h"

namespace comminterface
{

RosDeviceStatusPublisher::RosDeviceStatusPublisher(const std::string& topicName)
{

    mTopicName = topicName;

    _pub = n.advertise<device_msgs::Status>(topicName.c_str(), 1000);

    mLoopRate = 10;

    runThread = true;

}

RosDeviceStatusPublisher::~RosDeviceStatusPublisher()
{
    std::cout << "Deleting Publisher " << mTopicName << std::endl;

    stopThread();

    while(!this->isFinished())
    {
        std::cout << "Waiting for thread to finish" << std::endl;
        QThread::msleep(100);
    }

    _pub.shutdown();

    std::cout << "Deleted Publisher: " << mTopicName << std::endl;
}

void RosDeviceStatusPublisher::setDeviceStatus(const device_msgs::Status& data)
{
    //std::cout << "RosDeviceStatusPublisher setDeviceStatus " << mTopicName << std::endl;
    mStatusDataMutex.lock();
    mStatusData.deviceName = data.deviceName;
    mStatusData.mode = data.mode;
    mStatusData.action = data.action;
    mStatusData.actionIdentifier = data.actionIdentifier;
    mStatusData.result = data.result;
    mStatusData.timeStamp = data.timeStamp;
    mStatusDataMutex.unlock();
}

void RosDeviceStatusPublisher::getDeviceStatus(device_msgs::Status& data)
{
    //std::cout << "RosDeviceStatusPublisher getDeviceStatus " << mTopicName << std::endl;
    mStatusDataMutex.lock();
    data.deviceName = mStatusData.deviceName;
    data.mode = mStatusData.mode;
    data.action = mStatusData.action;
    data.actionIdentifier = mStatusData.actionIdentifier;
    data.result = mStatusData.result;
    data.timeStamp = mStatusData.timeStamp;
    mStatusDataMutex.unlock();
}

void RosDeviceStatusPublisher::setLoopRate(unsigned int rate)
{
    mLoopRate = rate;
}

void RosDeviceStatusPublisher::run()
{

    std::cout << "Starting Ros Comm Publisher: " << mTopicName << std::endl;

    ros::Rate loop_rate(mLoopRate);

    while (ros::ok() && runThread)
    {
        /**
                   * This is a message object. You stuff it with data, and then publish it.
                   */
        device_msgs::Status deviceStatus;
        getDeviceStatus(deviceStatus);

        //std::cout << "Sending deviceStatus data size "<< std::endl;
        //ROS_INFO("%s", msg.data.c_str());

        //std::cout << "Publishing Data" << std::endl;
        /**
                   * The publish() function is how you send messages. The parameter
                   * is the message object. The type of this object must agree with the type
                   * given as a template parameter to the advertise<>() call, as was done
                   * in the constructor above.
                   */
        _pub.publish(deviceStatus);

        ros::spinOnce();

        loop_rate.sleep();
    }

}

}
