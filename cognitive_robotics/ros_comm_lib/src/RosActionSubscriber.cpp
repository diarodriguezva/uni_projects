#include "RosActionSubscriber.h"

namespace comminterface
{

RosActionSubscriber::RosActionSubscriber(const std::string& topicName)
{
    mTopicName = topicName;

    ros::NodeHandle n;

    _sub = n.subscribe(topicName, 1000, &RosActionSubscriber::actionCallback, this);

    runThread = true;
}

RosActionSubscriber::~RosActionSubscriber()
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


void RosActionSubscriber::actionCallback(const ros_tum_msgs::ActionVecPtr& data)
{
    this->setActionData(data);
}

void RosActionSubscriber::setActionData(const ros_tum_msgs::ActionVecPtr& data)
{
    mActionDataMutex.lock();
    util::Util::clearActionData(mActionData);
    mActionData.ActionVec.resize(data->ActionVec.size());
    for(int i=0; i<data->ActionVec.size();++i)
    {
        mActionData.ActionVec[i].name = data->ActionVec[i].name;
        Util::copyActorData(data->ActionVec[i].actor, mActionData.ActionVec[i].actor);
        mActionData.ActionVec[i].uniqueIdentifier = data->ActionVec[i].uniqueIdentifier;
    }
    //std::cout << "Set Action Data " << mActionData.ActionVec.size() << std::endl;
    mActionDataMutex.unlock();
}

void RosActionSubscriber::getActionData(ros_tum_msgs::ActionVec& data)
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
    //std::cout << "get Action Data " << mActionData.ActionVec.size() << std::endl;
    mActionDataMutex.unlock();
}


void RosActionSubscriber::run()
{

    std::cout << "Starting Ros Comm Subscriber: " <<  mTopicName << std::endl;

    while (ros::ok() && runThread)
    {
        ros::getGlobalCallbackQueue()->callAvailable(ros::WallDuration(0.1));
        //std::cout << "Running " << std::endl;
    }

}



}
