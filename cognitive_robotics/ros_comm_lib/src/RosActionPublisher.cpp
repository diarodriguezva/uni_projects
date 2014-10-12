#include "RosActionPublisher.h"

namespace comminterface
{

RosActionPublisher::RosActionPublisher(const std::string& topicName)
{

    mTopicName = topicName;

    ros::NodeHandle n;

    _pub = n.advertise<ros_tum_msgs::ActionVec>(topicName.c_str(), 1000);

    mLoopRate = 10;

    runThread = true;

}

RosActionPublisher::~RosActionPublisher()
{

    std::cout << "Deleting Publisher: " << mTopicName << std::endl;

    stopThread();

    while(!this->isFinished())
    {
        std::cout << "Waiting for thread to finish" << std::endl;
        QThread::msleep(100);
    }

    _pub.shutdown();

    std::cout << "Deleted Publisher: " << mTopicName << std::endl;

}

void RosActionPublisher::setLoopRate(unsigned int rate)
{
    mLoopRate = rate;
}

void RosActionPublisher::setActionData(const ros_tum_msgs::ActionVec& data)
{
    mActionDataMutex.lock();
    util::Util::clearActionData(mActionData);
    mActionData.ActionVec.resize(data.ActionVec.size());
    for(int i=0; i<data.ActionVec.size();++i)
    {
        mActionData.ActionVec[i].name = data.ActionVec[i].name;
        Util::copyActorData(data.ActionVec[i].actor, mActionData.ActionVec[i].actor);
        mActionData.ActionVec[i].uniqueIdentifier = data.ActionVec[i].uniqueIdentifier;
    }
    mActionDataMutex.unlock();
}

void RosActionPublisher::getActionData(ros_tum_msgs::ActionVec& data)
{
    util::Util::clearActionData(data);
    mActionDataMutex.lock();
    data.ActionVec.resize(mActionData.ActionVec.size());
    for(int i=0; i<mActionData.ActionVec.size();++i)
    {
        data.ActionVec[i].name = mActionData.ActionVec[i].name;
        Util::copyActorData(mActionData.ActionVec[i].actor, data.ActionVec[i].actor);
        data.ActionVec[i].uniqueIdentifier = mActionData.ActionVec[i].uniqueIdentifier;
    }
    util::Util::clearActionData(mActionData);
    mActionDataMutex.unlock();
}

void RosActionPublisher::run()
{

    std::cout << "Starting Ros Comm Publisher: " << mTopicName << std::endl;

    ros::Rate loop_rate(mLoopRate);

    while (ros::ok() && runThread)
    {
        /**
               * This is a message object. You stuff it with data, and then publish it.
               */
        ros_tum_msgs::ActionVec actions;
        getActionData(actions);

        //std::cout << "Sending Action data size ######################################### " << actions.ActionVec.size() << std::endl;
        //ROS_INFO("%s", msg.data.c_str());

        //std::cout << "Publishing Data" << std::endl;
        /**
               * The publish() function is how you send messages. The parameter
               * is the message object. The type of this object must agree with the type
               * given as a template parameter to the advertise<>() call, as was done
               * in the constructor above.
               */

        if(actions.ActionVec.size()>0)
        {
            _pub.publish(actions);
        }

        //ros::spinOnce();

        loop_rate.sleep();
    }

}

}
