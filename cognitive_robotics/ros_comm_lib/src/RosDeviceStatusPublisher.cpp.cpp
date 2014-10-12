#include "RosDeviceStatusPublisher.h"

namespace comminterface
{

RosDeviceStatusPublisher::RosDeviceStatusPublisher(const std::string& topicName)
{

    mTopicName = topicName;

    ros::NodeHandle n;

    _pub = n.advertise<ros_tum_msgs::DeviceStatus>(topicName.c_str(), 1000);

    mLoopRate = 10;

    runThread = true;

}

RosDeviceStatusPublisher::~RosDeviceStatusPublisher()
{
    std::cout << "Deleting Publisher " << mTopicName << std::endl;

    this->wait();
}

void RosDeviceStatusPublisher::setDeviceStatus(const ros_tum_msgs::DeviceStatus& data)
{
    mStatusDataMutex.lock();
    mStatusData.deviceName = data.deviceName;
    mStatusData.mode = data.mode;
    mStatusData.action = data.action;
    mStatusData.actionIdentifier = data.actionIdentifier;
    mStatusData.result = data.result;
    mStatusData.timeStamp = data.timeStamp;
    mStatusDataMutex.unlock();
}

void RosDeviceStatusPublisher::getDeviceStatus(ros_tum_msgs::DeviceStatus& data)
{
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
        ros_tum_msgs::DeviceStatus deviceStatus;
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

        //ros::spinOnce();

        loop_rate.sleep();
    }

}

}
