#ifndef DETECTORTHREAD_H_
#define DETECTORTHREAD_H_

#include <iostream>
#include <string>
#include <QThread>
#include <QTime>
#include "detector/Detector.h"
#include <ros_tum_msgs/PerceptionState.h>
#include <ros_tum_msgs/PerceptionStateService.h>

class DetectorThread : public QThread
{
public:

    enum DetectorState
    {
        standby 		 = 0,
        detect   		 = 1,
        stop			 = 2
    };

    DetectorThread();

    virtual ~DetectorThread();

    detection::Detector* getDetectorPtr()
    {
        return mDetector;
    }

    void startThread()
    {
        runThread = true;
    }

    void stopThread()
    {
        runThread = false;
    }

    void getDetectorState(DetectorState& state)
    {
        stateMutex.lock();
        state=mDetectorState;
        stateMutex.unlock();

    }

    void setDetectorState(DetectorState& state)
    {
        stateMutex.lock();
        mDetectorState=state;
        stateMutex.unlock();
    }

    bool state_callback(ros_tum_msgs::PerceptionStateService::Request &req, ros_tum_msgs::PerceptionStateService::Response &res);


    virtual void run();

private:

    detection::Detector* mDetector;

    QMutex stateMutex;
    DetectorThread::DetectorState mDetectorState;

    ros::ServiceServer mDetectorStateService;

    bool runThread;
};

#endif /*DETECTORTHREAD_H_*/