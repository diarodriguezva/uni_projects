#include "comm_lib/ActorsPublisher.h"

namespace comminterface
{

ActorsPublisher::ActorsPublisher(const std::string& topicName)
{
    mTopicName = topicName;

    ros::NodeHandle n;

    _pub = n.advertise<actor_msgs::ActorVec>(topicName.c_str(), 10);

    mLoopRate = 1000;

    runThread = true;

}

ActorsPublisher::~ActorsPublisher()
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

void ActorsPublisher::setLoopRate(unsigned int rate)
{
    mLoopRate = rate;
}

void ActorsPublisher::setActorsData(const actor_msgs::ActorVec& data)
{
    mActorsDataMutex.lock();
    Util::clearActorsDataContainer(mActorsData);
    Util::copyActorDataContainer(data, mActorsData);
    mActorsDataMutex.unlock();
}

void ActorsPublisher::getActorsData(actor_msgs::ActorVec& data)
{
    Util::clearActorsDataContainer(data);
    mActorsDataMutex.lock();
    Util::copyActorDataContainer(mActorsData, data);
    mActorsDataMutex.unlock();
}


void ActorsPublisher::run()
{
    std::cout << "Starting Ros Comm Publisher " << mTopicName << std::endl;

    ros::Rate loop_rate(mLoopRate);

    while (ros::ok() && runThread)
    {
        /**
           * This is a message object. You stuff it with data, and then publish it.
           */
        actor_msgs::ActorVec actors;
        getActorsData(actors);

        std::cout << "actors pub " << actors.ActorVec.size() << std::endl;
        _pub.publish(actors);

        //ros::spinOnce();

    usleep(300);
        //loop_rate.sleep();
    }
}

}
