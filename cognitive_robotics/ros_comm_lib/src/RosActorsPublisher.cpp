#include "RosActorsPublisher.h"

namespace comminterface
{

RosActorsPublisher::RosActorsPublisher(const std::string& topicName)
{
    mTopicName = topicName;

    ros::NodeHandle n;

    _pub = n.advertise<ros_tum_msgs::ActorVec>(topicName.c_str(), 1000);

    mLoopRate = 10;

    runThread = true;

}

RosActorsPublisher::~RosActorsPublisher()
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

void RosActorsPublisher::setLoopRate(unsigned int rate)
{
    mLoopRate = rate;
}

void RosActorsPublisher::setActorsData(const ros_tum_msgs::ActorVec& data)
{
    //std::cout << "publisher set data " << std::endl;
    //std::cout << "data size " << data.ActorVec.size() << std::endl;
    mActorsDataMutex.lock();
    Util::clearActorsDataContainer(mActorsData);
    Util::copyActorDataContainer(data, mActorsData);
    mActorsDataMutex.unlock();
    //std::cout << "#########################################################################################################" << std::endl;
}

void RosActorsPublisher::getActorsData(ros_tum_msgs::ActorVec& data)
{
    Util::clearActorsDataContainer(data);
    mActorsDataMutex.lock();
    Util::copyActorDataContainer(mActorsData, data);
    mActorsDataMutex.unlock();
    //std::cout << "publisher get data " << std::endl;
    //std::cout << "data size " << data.ActorVec.size() << std::endl;
}


void RosActorsPublisher::run()
{
    std::cout << "Starting Ros Comm Publisher " << mTopicName << std::endl;

    ros::Rate loop_rate(mLoopRate);

    while (ros::ok() && runThread)
    {
        /**
           * This is a message object. You stuff it with data, and then publish it.
           */
        ros_tum_msgs::ActorVec actors;
        getActorsData(actors);

        _pub.publish(actors);

        //ros::spinOnce();

        loop_rate.sleep();
    }
}

}
