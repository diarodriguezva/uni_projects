#include "RosTaskStatusPublisher.h"

namespace comminterface
{

RosTaskStatusPublisher::RosTaskStatusPublisher(const std::string& topicName)
{

    mTopicName = topicName;

    ros::NodeHandle n;

    _pub = n.advertise<ros_tum_msgs::TaskStatusVec>(topicName.c_str(), 1000);

    mLoopRate = 10;

    runThread = true;

}

RosTaskStatusPublisher::~RosTaskStatusPublisher()
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

void RosTaskStatusPublisher::setTaskStatus(const ros_tum_msgs::TaskStatusVec& data)
{
    mStatusDataMutex.lock();
    mStatusData.TaskStatusVec.erase(mStatusData.TaskStatusVec.begin(), mStatusData.TaskStatusVec.end());
    mStatusData.TaskStatusVec.resize(data.TaskStatusVec.size());
    //std::cout << "setTaskStatus " << data.TaskStatusVec.size() << std::endl;
    for(int i=0; i<mStatusData.TaskStatusVec.size(); ++i)
    {
        mStatusData.TaskStatusVec[i].taskName=data.TaskStatusVec[i].taskName;

        mStatusData.TaskStatusVec[i].taskActions.erase(mStatusData.TaskStatusVec[i].taskActions.begin(), mStatusData.TaskStatusVec[i].taskActions.end());
        mStatusData.TaskStatusVec[i].taskActions.resize(data.TaskStatusVec[i].taskActions.size());

        mStatusData.TaskStatusVec[i].actionDoneStatus.erase(mStatusData.TaskStatusVec[i].actionDoneStatus.begin(), mStatusData.TaskStatusVec[i].actionDoneStatus.end());
        mStatusData.TaskStatusVec[i].actionDoneStatus.resize(data.TaskStatusVec[i].actionDoneStatus.size());
        for(int n=0; n<mStatusData.TaskStatusVec[i].taskActions.size(); ++n)
        {
            mStatusData.TaskStatusVec[i].taskActions[n]=data.TaskStatusVec[i].taskActions[n];
            mStatusData.TaskStatusVec[i].actionDoneStatus[n]=data.TaskStatusVec[i].actionDoneStatus[n];
        }
    }

    //std::cout << "setTaskStatus " << mStatusData.TaskStatusVec.size() << std::endl;

    mStatusDataMutex.unlock();
}

void RosTaskStatusPublisher::getTaskStatus(ros_tum_msgs::TaskStatusVec& data)
{
    data.TaskStatusVec.erase(data.TaskStatusVec.begin(), data.TaskStatusVec.end());
    mStatusDataMutex.lock();
    data.TaskStatusVec.resize(mStatusData.TaskStatusVec.size());
    for(int i=0; i<mStatusData.TaskStatusVec.size(); ++i)
    {
        data.TaskStatusVec[i].taskName=mStatusData.TaskStatusVec[i].taskName;

        data.TaskStatusVec[i].taskActions.erase(data.TaskStatusVec[i].taskActions.begin(), data.TaskStatusVec[i].taskActions.end());
        data.TaskStatusVec[i].taskActions.resize(mStatusData.TaskStatusVec[i].taskActions.size());

        data.TaskStatusVec[i].actionDoneStatus.erase(data.TaskStatusVec[i].actionDoneStatus.begin(), data.TaskStatusVec[i].actionDoneStatus.end());
        data.TaskStatusVec[i].actionDoneStatus.resize(mStatusData.TaskStatusVec[i].actionDoneStatus.size());
        for(int n=0; n<data.TaskStatusVec[i].taskActions.size(); ++n)
        {
            data.TaskStatusVec[i].taskActions[n]=mStatusData.TaskStatusVec[i].taskActions[n];
            data.TaskStatusVec[i].actionDoneStatus[n]=mStatusData.TaskStatusVec[i].actionDoneStatus[n];
        }
    }

    mStatusDataMutex.unlock();
}

void RosTaskStatusPublisher::setLoopRate(unsigned int rate)
{
    mLoopRate = rate;
}

void RosTaskStatusPublisher::run()
{

    std::cout << "Starting Ros Comm Publisher: " << mTopicName << std::endl;

    ros::Rate loop_rate(mLoopRate);

    while (ros::ok() && runThread)
    {
        /**
                   * This is a message object. You stuff it with data, and then publish it.
                   */
        ros_tum_msgs::TaskStatusVec taskStatus;
        getTaskStatus(taskStatus);

        //std::cout << "Sending taskStatus data size ######################################### " << taskStatus.TaskStatusVec.size() << std::endl;
        //ROS_INFO("%s", msg.data.c_str());

        //std::cout << "Publishing Data" << std::endl;
        /**
                   * The publish() function is how you send messages. The parameter
                   * is the message object. The type of this object must agree with the type
                   * given as a template parameter to the advertise<>() call, as was done
                   * in the constructor above.
                   */
        _pub.publish(taskStatus);

        //ros::spinOnce();

        loop_rate.sleep();
    }
}

}
