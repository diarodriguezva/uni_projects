#ifndef CAM_H_
#define CAM_H_

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "ros/ros.h"
#include <camera_srvs/CameraInfo.h>

using namespace std;

using namespace cv;

namespace caminput
{
class Cam
{
public:

    Cam(int id, std::string service_name);

    virtual ~Cam();

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual void getImageCopy(cv::Mat& inputImage) = 0;

    unsigned int getSensorWidth()
    {
        return mWidth;
    }

    unsigned int getSensorHeight()
    {
        return mHeight;
    }

    void loadIntrinsics(std::string filename);

    void loadExtrinsics(std::string filename);

    bool cameraInfo_callback(camera_srvs::CameraInfo::Request &req, camera_srvs::CameraInfo::Response &res);


public:

    cv::Mat intrinsics;

    cv::Mat extrinsics;

    cv::Mat T_inv;

    cv::Mat projection;

    int mId;

    int mWidth;

    int mHeight;

    ros::ServiceServer mCalibInfoService;
    std::string mServiceName;

};
};

#endif /*CAM_H_*/
