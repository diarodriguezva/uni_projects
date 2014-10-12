#include "RosRobotStatusPublisher.h"

namespace comminterface
{

RosRobotStatusPublisher::RosRobotStatusPublisher(const std::string& topicName)
{

    mTopicName = topicName;

    ros::NodeHandle n;

    _pub = n.advertise<ros_tum_msgs::RobotStatus>(topicName.c_str(), 1000);

    mLoopRate = 10;

    runThread = true;

}

RosRobotStatusPublisher::~RosRobotStatusPublisher()
{
    std::cout << "Deleting Publisher " << mTopicName << std::endl;

    this->wait();
}

void RosRobotStatusPublisher::setRobotStatus(const ros_tum_msgs::RobotStatus& data)
{
    mStatusDataMutex.lock();
    mStatusData.mode = data.mode;
    mStatusData.action = data.action;
    mStatusData.actionIdentifier = data.actionIdentifier;
    mStatusData.timeStamp = data.timeStamp;
    mStatusDataMutex.unlock();
}

void RosRobotStatusPublisher::getRobotStatus(ros_tum_msgs::RobotStatus& data)
{
    mStatusDataMutex.lock();
    data.mode = mStatusData.mode;
    data.action = mStatusData.action;
    data.actionIdentifier = mStatusData.actionIdentifier;
    data.timeStamp = mStatusData.timeStamp;
    mStatusDataMutex.unlock();
}

void RosRobotStatusPublisher::setLoopRate(unsigned int rate)
{
    mLoopRate = rate;
}

void RosRobotStatusPublisher::run()
{

    std::cout << "Starting Ros Comm Publisher: " << mTopicName << std::endl;

    ros::Rate loop_rate(mLoopRate);

    while (ros::ok() && runThread)
    {
        /**
                   * This is a message object. You stuff it with data, and then publish it.
                   */
        ros_tum_msgs::RobotStatus robotStatus;
        getRobotStatus(robotStatus);

        //std::cout << "Sending robotStatus data size "<< std::endl;
        //ROS_INFO("%s", msg.data.c_str());

        //std::cout << "Publishing Data" << std::endl;
        /**
                   * The publish() function is how you send messages. The parameter
                   * is the message object. The type of this object must agree with the type
                   * given as a template parameter to the advertise<>() call, as was done
                   * in the constructor above.
                   */
        _pub.publish(robotStatus);

        //ros::spinOnce();

        loop_rate.sleep();
    }

}

}
