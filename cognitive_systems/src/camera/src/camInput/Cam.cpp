#include <camera/camInput/Cam.h>
#include <ros/package.h>

namespace caminput
{

Cam::Cam(int id, std::string service_name)
{
    mId = id;
    mServiceName=service_name;

    std::string filename = ros::package::getPath("camera") + "/config/cam.xml";

    loadIntrinsics(filename);
    loadExtrinsics(filename);

    cv::Mat intrinsics_pad(3,4, DataType<double>::type);

    for(int i=0; i < intrinsics.rows; ++i)
    {
        for(int j=0; j < intrinsics.cols; ++j)
        {
            intrinsics_pad.at<double>(i,j) = intrinsics.at<double>(i,j);
        }
    }
    intrinsics_pad.at<double>(0,3) = 0.0;
    intrinsics_pad.at<double>(1,3) = 0.0;
    intrinsics_pad.at<double>(2,3) = 0.0;

    projection = intrinsics_pad * extrinsics;
    std::cout << "projection extrinsics matrix" <<std::endl;
    std::cout << projection << std::endl;

    ros::NodeHandle _n;
    mCalibInfoService = _n.advertiseService(mServiceName, &Cam::cameraInfo_callback, this);

}

Cam::~Cam()
{
    mCalibInfoService.shutdown();
}


void Cam::loadIntrinsics(std::string filename)
{
    FileStorage fs(filename, FileStorage::READ);
    if(fs.isOpened())
    {
        fs["intrinsics"] >> intrinsics;
        fs.release();
        std::cout << "camera intrinsics matrix: " << intrinsics << std::endl;
    }
    else
    {
        std::cout << "Could not open file " << filename << std::endl;
        throw;
    }

}

void Cam::loadExtrinsics(std::string filename)
{
    FileStorage fs(filename, FileStorage::READ);
    if(fs.isOpened())
    {
        fs["extrinsics"] >> extrinsics;
        fs.release();
        std::cout << "camera extrinsics matrix: " << extrinsics << std::endl;
    }
    else
    {
        std::cout << "Could not open file " << filename << std::endl;
        throw;
    }
}

bool Cam::cameraInfo_callback(camera_srvs::CameraInfo::Request &req, camera_srvs::CameraInfo::Response &res)
{
    res.response.width=mWidth;
    res.response.height=mHeight;
    res.response.encoding="BGR";

    double *input = (double*)(intrinsics.data);
    for(int i=0;i<9;++i)
    {
        res.response.K[i]=input[i];
        std::cout << "res.response.K[i] " << res.response.K[i] << std::endl;
    }

    double *input1 = (double*)(extrinsics.data);
    for(int i=0;i<16;++i)
    {
        res.response.E[i]=input1[i];
    }


    double *input2 = (double*)(projection.data);
    for(int i=0;i<12;++i)
    {
        res.response.P[i]=input2[i];
    }

    return true;
}

}



