#include "RosTaskStatusSubscriber.h"

namespace comminterface
{

RosTaskStatusSubscriber::RosTaskStatusSubscriber(const std::string& topicName)
{
    mTopicName = topicName;

    ros::NodeHandle n;

    _sub = n.subscribe(topicName, 1000, &RosTaskStatusSubscriber::taskStatusCallback, this);

    runThread = true;
}

RosTaskStatusSubscriber::~RosTaskStatusSubscriber()
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

void RosTaskStatusSubscriber::taskStatusCallback(const ros_tum_msgs::TaskStatusVecConstPtr& data)
{
    this->setTaskStatus(data);
}

void RosTaskStatusSubscriber::setTaskStatus(const ros_tum_msgs::TaskStatusVecConstPtr& data)
{
    mStatusMutex.lock();
    mTaskStatus.TaskStatusVec.erase(mTaskStatus.TaskStatusVec.begin(), mTaskStatus.TaskStatusVec.end());
    mTaskStatus.TaskStatusVec.resize(data->TaskStatusVec.size());
    for(int i=0; i<mTaskStatus.TaskStatusVec.size(); ++i)
    {
        mTaskStatus.TaskStatusVec[i].taskName=data->TaskStatusVec[i].taskName;

        mTaskStatus.TaskStatusVec[i].taskActions.erase(mTaskStatus.TaskStatusVec[i].taskActions.begin(), mTaskStatus.TaskStatusVec[i].taskActions.end());
        mTaskStatus.TaskStatusVec[i].taskActions.resize(data->TaskStatusVec[i].taskActions.size());

        mTaskStatus.TaskStatusVec[i].actionDoneStatus.erase(mTaskStatus.TaskStatusVec[i].actionDoneStatus.begin(), mTaskStatus.TaskStatusVec[i].actionDoneStatus.end());
        mTaskStatus.TaskStatusVec[i].actionDoneStatus.resize(data->TaskStatusVec[i].actionDoneStatus.size());
        for(int n=0; n<mTaskStatus.TaskStatusVec[i].taskActions.size(); ++n)
        {
            mTaskStatus.TaskStatusVec[i].taskActions[n]=data->TaskStatusVec[i].taskActions[n];
            mTaskStatus.TaskStatusVec[i].actionDoneStatus[n]=data->TaskStatusVec[i].actionDoneStatus[n];
        }
    }

    mStatusMutex.unlock();
}

void RosTaskStatusSubscriber::getTaskStatus(ros_tum_msgs::TaskStatusVec& data)
{
    data.TaskStatusVec.erase(data.TaskStatusVec.begin(), data.TaskStatusVec.end());
    mStatusMutex.lock();
    data.TaskStatusVec.resize(mTaskStatus.TaskStatusVec.size());
    for(int i=0; i<mTaskStatus.TaskStatusVec.size(); ++i)
    {
        data.TaskStatusVec[i].taskName=mTaskStatus.TaskStatusVec[i].taskName;

        data.TaskStatusVec[i].taskActions.erase(data.TaskStatusVec[i].taskActions.begin(), data.TaskStatusVec[i].taskActions.end());
        data.TaskStatusVec[i].taskActions.resize(mTaskStatus.TaskStatusVec[i].taskActions.size());

        data.TaskStatusVec[i].actionDoneStatus.erase(data.TaskStatusVec[i].actionDoneStatus.begin(), data.TaskStatusVec[i].actionDoneStatus.end());
        data.TaskStatusVec[i].actionDoneStatus.resize(mTaskStatus.TaskStatusVec[i].actionDoneStatus.size());
        for(int n=0; n<data.TaskStatusVec[i].taskActions.size(); ++n)
        {
            data.TaskStatusVec[i].taskActions[n]=mTaskStatus.TaskStatusVec[i].taskActions[n];
            data.TaskStatusVec[i].actionDoneStatus[n]=mTaskStatus.TaskStatusVec[i].actionDoneStatus[n];
        }
    }

    mStatusMutex.unlock();
}

void RosTaskStatusSubscriber::run()
{

    std::cout << "Starting Ros Comm Subscriber: " << mTopicName << std::endl;

    while (ros::ok() && runThread)
    {
        ros::getGlobalCallbackQueue()->callAvailable(ros::WallDuration(0.1));
    }

}



}
