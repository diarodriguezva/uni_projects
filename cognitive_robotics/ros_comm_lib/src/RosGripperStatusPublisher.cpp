#include "RosGripperStatusPublisher.h"

namespace comminterface
{

RosGripperStatusPublisher::RosGripperStatusPublisher(const std::string& topicName)
{

    mTopicName = topicName;

    ros::NodeHandle n;

    _pub = n.advertise<ros_tum_msgs::GripperStatus>(topicName.c_str(), 1000);

    mLoopRate = 10;

    runThread = true;

}

RosGripperStatusPublisher::~RosGripperStatusPublisher()
{
    std::cout << "Deleting Publisher: " <<  mTopicName << std::endl;

    this->wait();
}

void RosGripperStatusPublisher::setGripperStatus(const ros_tum_msgs::GripperStatus& data)
{
    mStatusDataMutex.lock();
    mStatusData.mode = data.mode;
    mStatusData.actionName = data.actionName;
    mStatusData.actionIdentifier = data.actionIdentifier;
    mStatusData.timeStamp = data.timeStamp;
    mStatusDataMutex.unlock();
}

void RosGripperStatusPublisher::getGripperStatus(ros_tum_msgs::GripperStatus& data)
{
    mStatusDataMutex.lock();
    data.mode = mStatusData.mode;
    data.actionName = mStatusData.actionName;
    data.actionIdentifier = mStatusData.actionIdentifier;
    data.timeStamp = mStatusData.timeStamp;
    mStatusDataMutex.unlock();
}

void RosGripperStatusPublisher::setLoopRate(unsigned int rate)
{
    mLoopRate = rate;
}

void RosGripperStatusPublisher::run()
{

    std::cout << "Starting Ros Comm Publisher: "  << mTopicName << std::endl;

    ros::Rate loop_rate(mLoopRate);

    while (ros::ok() && runThread)
    {
        /**
                   * This is a message object. You stuff it with data, and then publish it.
                   */
        ros_tum_msgs::GripperStatus gripperStatus;
        getGripperStatus(gripperStatus);

        //std::cout << "Sending gripperStatus " << std::endl;
        //ROS_INFO("%s", msg.data.c_str());

        //std::cout << "Publishing Data" << std::endl;
        /**
                   * The publish() function is how you send messages. The parameter
                   * is the message object. The type of this object must agree with the type
                   * given as a template parameter to the advertise<>() call, as was done
                   * in the constructor above.
                   */
        _pub.publish(gripperStatus);

        //ros::spinOnce();

        loop_rate.sleep();
    }
}

}
