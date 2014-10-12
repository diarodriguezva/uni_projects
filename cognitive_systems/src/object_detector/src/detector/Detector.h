#ifndef DETECTOR_H_
#define DETECTOR_H_

#include <iostream>
#include <stdio.h>
#include <QSettings>
#include <QFileInfo>
#include <QMutex>
#include <opencv2/opencv.hpp>
#include <comm_lib/ImageSubscriber.h>
#include <comm_lib/ActorsPublisher.h>

#include <vector>
#include <camera_srvs/CameraInfo.h>

#include <ros/package.h>

#define DEG2RAD 3.14159265/180.0

using namespace cv;

namespace detection
{

class Detector
{
public:

    //Constructor
    Detector();

    /** @brief Destructor (empty). */
    ~Detector();

    void standBy();

    void detectObjects();

    void getOutputImg(cv::Mat& img)
    {
        mOutputImgMutex.lock();
        img=mOutputImg;
        mOutputImgMutex.unlock();
    }

    void getColourSegmentedImg(cv::Mat& img)
    {
        mColourSegmentedImgMutex.lock();
        img=mColourSegmentedImg;
        mColourSegmentedImgMutex.unlock();
    }

    void setColourSegmentedImg(cv::Mat& img)
    {
        mColourSegmentedImgMutex.lock();
        mColourSegmentedDispImg=img;
        mColourSegmentedImgMutex.unlock();
    }

    cv::Mat& getContourImg()
    {
        //mContourDispImgMutex.lock();
        return mContourDispImg;
        //mContourDispImgMutex.unlock();
    }

    void initCalibrationdata();

    void checkCalibration();

    void checkROI();

    void drawROI();

    bool insidePolygon(cv::Point2i *polygon, int N, cv::Point2i p);

    //with known z
    void getScreenTo3DPoints(const cv::Point2i& screenPoint, cv::Point3d& point3D, double z);

    void get3DToScreenPoints(const cv::Point3d& point3D, cv::Point2i& screenPoint);

    void setColourSegDebug(bool ON)
    {
        debugSeg = ON;
    }


private:

    void parseConifgFile();

    void generatePixelVecForROI();

    bool updateInputImg();

    void preProcess();

    void updateColourSegmentedImg();

    void updateCountourImage();

    void computeTragetsBoundingBox();

    void compute3DPosition();

    void updateTargetContainer();

    void updateOutputImg();

private:


    std::string CAMERA_IMAGE_TOPIC_NAME;
    std::string CAMERA_INFO_SERVICE_NAME;

    std::string TARGETS_PUBLISHER_TOPIC_NAME;

    //Number of colours
    unsigned int N_COLOURED_TARGETS;

    std::vector<std::string > TARGET_COLOUR_NAMES;

    std::vector<bool > TARGET_COLOUR_ENABLE;

    //Colour Thresholds vector (each entry holds upper and lower thresholds)
    std::vector<cv::Vec2i > mHThresholds;
    std::vector<cv::Vec2i > mSThresholds;

    std::vector<cv::Vec3b > TARGET_COLOUR_CODE;

    double OFFSET_X;
    double OFFSET_Y;
    double OFFSET_Z;

    bool ROI_ENABLE;
    double P_0_X;
    double P_0_Y;
    double P_0_Z;
    double P_1_X;
    double P_1_Y;
    double P_1_Z;
    double P_2_X;
    double P_2_Y;
    double P_2_Z;
    double P_3_X;
    double P_3_Y;
    double P_3_Z;

    cv::Point3d cubes_robotOffset;

    double cubes_robotSafety_min;

    double cubes_robotSafety_max;

    int safety_radius_min;

    int safety_radius_max;

    std::vector<cv::Point2i> pixelVec;

    cv::Mat mInputImg;
    cv::Mat mHSVImg;

    cv::Mat mOutputImg;
    QMutex  mOutputImgMutex;

    std::vector<cv::Mat> targetImgVec;
    cv::Mat mColourSegmentedImg;
    cv::Mat mColourSegmentedDispImg;
    QMutex  mColourSegmentedImgMutex;
    bool debugSeg;

    cv::Mat mContourImg;
    cv::Mat mContourDispImg;
    QMutex  mContourDispImgMutex;

    cv::Mat mTmpImg;

    int mWidth;
    int mHeight;
    cv::Mat intrinsicsMat;
    cv::Mat extrinsicsMat;
    cv::Mat projectionMat;

    comminterface::ActorsPublisher* mPub;
    comminterface::ImageSubscriber* mSub;



};

}; //namespace tracking


#endif /*DETECTOR_H_*/
