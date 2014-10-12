#include "comm_lib/ActorsSubscriber.h"


namespace comminterface
{

ActorsSubscriber::ActorsSubscriber(const std::string& topicName)
{
    mTopicName = topicName;

    _sub = n.subscribe(topicName, 1000, &ActorsSubscriber::actorCallback, this);

    runThread = true;
}

ActorsSubscriber::~ActorsSubscriber()
{
    std::cout << "Deleting Subscriber " << mTopicName << std::endl;

    stopThread();

    while(!this->isFinished())
    {
        std::cout << "Waiting for thread to finish" << std::endl;
        QThread::msleep(100);
    }

    _sub.shutdown();

    std::cout << "Deleted Subscriber " << mTopicName << std::endl;

}

void ActorsSubscriber::actorCallback(const actor_msgs::ActorVecConstPtr& data)
{
    //std::cout << "actorCallback" << std::endl;
    this->setActorsData(data);
}

void ActorsSubscriber::setActorsData(const actor_msgs::ActorVecConstPtr& data)
{
    mActorsDataMutex.lock();

    util::Util::clearActorsDataContainer(mActorData);

    //std::cout << "set size +++++++++++++++++++++++++++++++++++++++ " << data->ActorVec.size() << std::endl;

    mActorData.ActorVec.resize(data->ActorVec.size());

    for(int i=0; i < mActorData.ActorVec.size();++i)
    {
        mActorData.ActorVec[i].targetPoseVec.resize(data->ActorVec[i].targetPoseVec.size());
        for(int t=0; t < mActorData.ActorVec[i].targetPoseVec.size();++t)
        {
            mActorData.ActorVec[i].targetPoseVec[t].position.x=data->ActorVec[i].targetPoseVec[t].position.x;
            mActorData.ActorVec[i].targetPoseVec[t].position.y=data->ActorVec[i].targetPoseVec[t].position.y;
            mActorData.ActorVec[i].targetPoseVec[t].position.z=data->ActorVec[i].targetPoseVec[t].position.z;
            mActorData.ActorVec[i].targetPoseVec[t].orientation.x=data->ActorVec[i].targetPoseVec[t].orientation.x;
            mActorData.ActorVec[i].targetPoseVec[t].orientation.y=data->ActorVec[i].targetPoseVec[t].orientation.y;
            mActorData.ActorVec[i].targetPoseVec[t].orientation.z=data->ActorVec[i].targetPoseVec[t].orientation.z;
            mActorData.ActorVec[i].targetPoseVec[t].orientation.w=data->ActorVec[i].targetPoseVec[t].orientation.w;
        }
        mActorData.ActorVec[i].targetType = data->ActorVec[i].targetType;
        mActorData.ActorVec[i].targetProperty = data->ActorVec[i].targetProperty;
        mActorData.ActorVec[i].timeStamp = data->ActorVec[i].timeStamp;
        mActorData.ActorVec[i].targetId = data->ActorVec[i].targetId;
    }
    mActorsDataMutex.unlock();
    //        std::cout << "setActorsData done " << std::endl;
}

void ActorsSubscriber::getActorsData(actor_msgs::ActorVec& data)
{
    //std::cout << "getActorsData" << std::endl;
    mActorsDataMutex.lock();

    util::Util::clearActorsDataContainer(data);

    data.ActorVec.resize(mActorData.ActorVec.size());
    //std::cout << "get size +++++++++++++++++++++++++++++++++++++++ " << data.ActorVec.size() << std::endl;
    for(int i=0; i < mActorData.ActorVec.size();++i)
    {
        data.ActorVec[i].targetPoseVec.resize(mActorData.ActorVec[i].targetPoseVec.size());
        for(int t=0; t < mActorData.ActorVec[i].targetPoseVec.size();++t)
        {
            data.ActorVec[i].targetPoseVec[t].position.x=mActorData.ActorVec[i].targetPoseVec[t].position.x;
            data.ActorVec[i].targetPoseVec[t].position.y=mActorData.ActorVec[i].targetPoseVec[t].position.y;
            data.ActorVec[i].targetPoseVec[t].position.z=mActorData.ActorVec[i].targetPoseVec[t].position.z;
            data.ActorVec[i].targetPoseVec[t].orientation.x=mActorData.ActorVec[i].targetPoseVec[t].orientation.x;
            data.ActorVec[i].targetPoseVec[t].orientation.y=mActorData.ActorVec[i].targetPoseVec[t].orientation.y;
            data.ActorVec[i].targetPoseVec[t].orientation.z=mActorData.ActorVec[i].targetPoseVec[t].orientation.z;
            data.ActorVec[i].targetPoseVec[t].orientation.w=mActorData.ActorVec[i].targetPoseVec[t].orientation.w;
        }
        data.ActorVec[i].targetType = mActorData.ActorVec[i].targetType;
        data.ActorVec[i].targetProperty = mActorData.ActorVec[i].targetProperty;
        data.ActorVec[i].timeStamp = mActorData.ActorVec[i].timeStamp;
        data.ActorVec[i].targetId = mActorData.ActorVec[i].targetId;
    }
    mActorsDataMutex.unlock();
    //std::cout << "getActorsData done " << std::endl;
}

void ActorsSubscriber::run()
{
    std::cout << "Starting Ros Comm Subscriber: " << mTopicName << std::endl;

    while (ros::ok() && runThread)
    {
        ros::getGlobalCallbackQueue()->callAvailable(ros::WallDuration(0.1));
        //std::cout << "Running " << std::endl;

        ros::spinOnce();
    }
}

}
