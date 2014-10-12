#include "DetectorThread.h"

using namespace std;

DetectorThread::DetectorThread()
{
    //Tracker instance
    mDetector = new detection::Detector();

    mDetectorState = DetectorThread::detect;

    ros::NodeHandle _n;
    mDetectorStateService = _n.advertiseService("DETECTOR_STATE_SERVICE", &DetectorThread::state_callback, this);

    runThread = true;

}

DetectorThread::~DetectorThread()
{
    runThread = false;

    usleep(100000);

    mDetectorStateService.shutdown();

    delete mDetector;

    usleep(100000);

    wait(100);
    if(isRunning())
    {
        terminate();
        wait(); // needed for UNIX systems
    }
}

bool DetectorThread::state_callback(ros_tum_msgs::PerceptionStateService::Request &req, ros_tum_msgs::PerceptionStateService::Response &res)
{
    DetectorState state;
    if(req.request == ros_tum_msgs::PerceptionState::STANDBY)
        state=DetectorThread::standby;
    else if(req.request == ros_tum_msgs::PerceptionState::ACTIVE)
        state=DetectorThread::detect;
    else
        state=DetectorThread::standby;

    setDetectorState(state);
}

void DetectorThread::run()
{

    DetectorState state;
    while(runThread)
    {
        getDetectorState(state);
        switch (state)
        {
        case DetectorThread::standby:
            mDetector->standBy();
            break;

        case DetectorThread::detect:
            mDetector->detectObjects();
            break;

        default:
            mDetector->standBy();
            break;

        }

        QThread::msleep(10);
    }
}


