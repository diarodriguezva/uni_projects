#ifndef TRACKER_H_
#define TRACKER_H_

#include "ParticleFilter.h"
#include <QString>
#include <ros_tum_msgs/CameraInfo.h>
#include "ros/ros.h"
#include <ros_comm_lib/RosImageSubscriber.h>
#include <ros_comm_lib/RosActorsPublisher.h>

using namespace std;

typedef  vector<vector<double > > Histogram2D;

namespace tracking1
{
class Tracker
{
public:

    struct Target
    {
        //x y s
        cv::Vec3d pose;
        double x_dim;
        double y_dim;
        Histogram2D histogram;
    };

    Tracker();

    ~Tracker();

    void init();

    bool process();

    void computeRefHistogram(cv::Mat& input);

    double computeBhattDist(Histogram2D& hist, Histogram2D& refHist);

    double computeLikelihood(cv::Mat& input, cv::Vec3d& pose);

    void parseConifgFile();

    void trackNext1();

    void getPose(cv::Vec3d& pose);

    void drawPose(cv::Vec3d& pose, cv::Scalar& color, int lineSize);

    void setOutputImg();

    void getOutputImage(cv::Mat& img);

public:


    std::string CAMERA_IMAGE_TOPIC_NAME;
    std::string CAMERA_INFO_SERVICE_NAME;

    int mWidth;
    int mHeight;

    int mBins;

    Target mTarget;
    ParticleFilter mFilter;

    unsigned int lut_1[256];

    cv::Mat mInImg;
    cv::Mat mHSVImg;
    cv::Mat mOutputImg;
    Histogram2D mCurrentHistogram;

    bool PRINT_AVG_LIKELIHOOD;
    bool PRINT_MAX_LIKELIHOOD;
    bool PRINT_PARTICLE_LIKELIHOOD;
    bool DRAW_PARTICLES;

    comminterface::RosImageSubscriber* mSub;

    std::string VS_TARGET_TOPIC_NAME;
    comminterface::RosActorsPublisher* mPub;
    ros_tum_msgs::ActorVec mTargetVec;

};


}; //namespace tracking1


#endif /*TRACKERDATA_H_*/
