#include "Detector.h"
#include <sstream>
#include <QStringList>

namespace detection
{

Detector::Detector()
{
    parseConifgFile();

    initCalibrationdata();

    cv::Size camSize = cv::Size(mWidth,mHeight);

    mInputImg =  cv::Mat(camSize, CV_8UC3);

    mHSVImg =  cv::Mat(camSize, CV_8UC3);

    targetImgVec.resize(N_COLOURED_TARGETS);
    for(int i = 0; i < targetImgVec.size(); ++i)
    {
        targetImgVec[i] = cv::Mat( camSize, CV_8UC1);
    }

    mColourSegmentedImg =  cv::Mat( camSize, CV_8UC3);

    mColourSegmentedDispImg =  cv::Mat( camSize, CV_8UC3);

    debugSeg = true;

    mContourImg =  cv::Mat( camSize, CV_8UC1);

    mContourDispImg =  cv::Mat( camSize, CV_8UC3);

    mTmpImg =  cv::Mat( camSize, CV_8UC1);

    mOutputImg = cv::Mat( camSize, CV_8UC3);

    generatePixelVecForROI();

    mPub = new comminterface::RosActorsPublisher(TARGETS_PUBLISHER_TOPIC_NAME);
    mSub = new comminterface::RosImageSubscriber(CAMERA_IMAGE_TOPIC_NAME);
    mSub->start();
    mPub->start();
}

Detector::~Detector()
{
    mInputImg.release();

    mHSVImg.release();

    for(int i = 0; i < targetImgVec.size(); ++i)
    {
        targetImgVec[i].release();
    }

    mColourSegmentedImg.release();

    mContourImg.release();

    mContourDispImg.release();

    mColourSegmentedDispImg.release();

    mTmpImg.release();

    mOutputImg.release();

    mPub->stopThread();

    mSub->stopThread();

    delete mPub;

    delete mSub;

}

void Detector::parseConifgFile()
{
    QString filename("config.ini");
    QFileInfo config(filename);

    if(!config.exists())
    {
        std::cout<<"error reading config.ini file"<<std::endl;
        throw;
    }

    QSettings iniFile(filename, QSettings::IniFormat);

    iniFile.beginGroup("CAMERA");
    CAMERA_IMAGE_TOPIC_NAME = iniFile.value("CAMERA_IMAGE_TOPIC_NAME", "").toString().toStdString();
    CAMERA_INFO_SERVICE_NAME = iniFile.value("CAMERA_INFO_SERVICE_NAME", "").toString().toStdString();
    std::cout << "CAMERA_IMAGE_TOPIC_NAME " << CAMERA_IMAGE_TOPIC_NAME << std::endl;
    std::cout << "CAMERA_INFO_SERVICE_NAME " << CAMERA_INFO_SERVICE_NAME << std::endl;
    iniFile.endGroup();

    iniFile.beginGroup("TARGETS_PUBLISHER");
    TARGETS_PUBLISHER_TOPIC_NAME = iniFile.value("TARGETS_PUBLISHER_TOPIC_NAME", "").toString().toStdString();
    std::cout << "TARGETS_PUBLISHER_TOPIC_NAME " << TARGETS_PUBLISHER_TOPIC_NAME << std::endl;
    iniFile.endGroup();

    iniFile.beginGroup("TARGETS");
    N_COLOURED_TARGETS = iniFile.value("N_COLOURED_TARGETS", 0).toInt();
    std::cout << "N_COLOURED_TARGETS " << N_COLOURED_TARGETS << std::endl;
    iniFile.endGroup();

    iniFile.beginGroup("TARGET_COLOUR_NAMES");
    TARGET_COLOUR_NAMES.clear();
    TARGET_COLOUR_NAMES.resize(N_COLOURED_TARGETS);
    for(unsigned int n = 0; n < N_COLOURED_TARGETS; ++n)
    {
        std::stringstream target_name;
        target_name.clear();
        target_name << "COLOUR_" << n;
        TARGET_COLOUR_NAMES[n] = iniFile.value(target_name.str().c_str(), " ").toString().toStdString();
        std::cout << "TARGET_COLOUR_NAMES " << n << " " << TARGET_COLOUR_NAMES[n] << std::endl;
    }
    iniFile.endGroup();

    iniFile.beginGroup("TARGET_COLOUR_ENABLE");
    TARGET_COLOUR_ENABLE.clear();
    TARGET_COLOUR_ENABLE.resize(N_COLOURED_TARGETS);
    for(unsigned int n = 0; n < N_COLOURED_TARGETS; ++n)
    {
        std::stringstream target_name;
        target_name.clear();
        target_name << "COLOUR_" << n;
        TARGET_COLOUR_ENABLE[n] = iniFile.value(target_name.str().c_str(), " ").toBool();
        std::cout << "TARGET_COLOUR_ENABLE " << n << " " << (int)TARGET_COLOUR_ENABLE[n] << std::endl;
    }
    iniFile.endGroup();


    mHThresholds.resize(N_COLOURED_TARGETS);
    iniFile.beginGroup("HSV_H_LOW_THRESHOLD");
    for(unsigned int n = 0; n < N_COLOURED_TARGETS; ++n)
    {
        std::stringstream name_h_lower_threshold;
        name_h_lower_threshold.clear();
        name_h_lower_threshold << "COLOUR_" << n << "_H_LOW" ;
        mHThresholds[n][0] = iniFile.value(name_h_lower_threshold.str().c_str(), " ").toInt();
        std::cout << name_h_lower_threshold.str() << " " << mHThresholds[n][0] << std::endl;
    }
    iniFile.endGroup();

    iniFile.beginGroup("HSV_H_HIGH_THRESHOLD");
    for(unsigned int n = 0; n < N_COLOURED_TARGETS; ++n)
    {
        std::stringstream name_h_higher_threshold;
        name_h_higher_threshold.clear();
        name_h_higher_threshold << "COLOUR_" << n << "_H_HIGH" ;
        mHThresholds[n][1] = iniFile.value(name_h_higher_threshold.str().c_str(), " ").toInt();
        std::cout << name_h_higher_threshold.str() << " " << mHThresholds[n][1] << std::endl;
    }
    iniFile.endGroup();

    mSThresholds.resize(N_COLOURED_TARGETS);
    iniFile.beginGroup("HSV_S_LOW_THRESHOLD");
    for(unsigned int n = 0; n < N_COLOURED_TARGETS; ++n)
    {
        std::stringstream name_s_lower_threshold;
        name_s_lower_threshold.clear();
        name_s_lower_threshold << "COLOUR_" << n << "_S_LOW" ;
        mSThresholds[n][0] = iniFile.value(name_s_lower_threshold.str().c_str(), " ").toInt();
        std::cout << name_s_lower_threshold.str() << " " << mSThresholds[n][0] << std::endl;
    }
    iniFile.endGroup();

    iniFile.beginGroup("HSV_S_HIGH_THRESHOLD");
    for(unsigned int n = 0; n < N_COLOURED_TARGETS; ++n)
    {
        std::stringstream name_s_higher_threshold;
        name_s_higher_threshold.clear();
        name_s_higher_threshold << "COLOUR_" << n << "_S_HIGH" ;
        mSThresholds[n][1] = iniFile.value(name_s_higher_threshold.str().c_str(), " ").toInt();
        std::cout << name_s_higher_threshold.str() << " " << mSThresholds[n][1] << std::endl;
    }
    iniFile.endGroup();

    iniFile.beginGroup("TARGET_COLOUR_CODE");
    TARGET_COLOUR_CODE.clear();
    TARGET_COLOUR_CODE.resize(N_COLOURED_TARGETS);
    for(unsigned int n = 0; n < N_COLOURED_TARGETS; ++n)
    {
        std::stringstream target_name;
        target_name.clear();
        target_name << "COLOUR_" << n;

        std::string code_string;
        code_string = iniFile.value(target_name.str().c_str(), " ").toString().toStdString();
        std::cout << "code_string " << code_string << std::endl;

        QString code_string_qt(code_string.c_str());
        QStringList colors = code_string_qt.split("_");
        for(int i=0;i<colors.size();++i)
        {
            std::cout << "Color code " << i << " " << colors[i].toStdString() << std::endl;
        }

        if(colors.size()!=3)
        {
            std::cout << "TARGET_COLOUR_CODE in config file should be in the format B_G_R" << std::endl;
            throw;
        }
        TARGET_COLOUR_CODE[n] = cv::Vec3b((uchar)colors[0].toInt(), (uchar)colors[1].toInt(),(uchar)colors[2].toInt());


        //std::cout << TARGET_COLOUR_CODE << n << " " << TARGET_COLOUR_CODE[n] << std::endl;
    }
    iniFile.endGroup();

    iniFile.beginGroup("ORIGIN_OFFSET");
    OFFSET_X = iniFile.value("OFFSET_X", 0.0).toDouble();
    OFFSET_Y = iniFile.value("OFFSET_Y", 0.0).toDouble();
    OFFSET_Z = iniFile.value("OFFSET_Z", 0.0).toDouble();
    std::cout << "ORIGIN_OFFSET " << OFFSET_X << " " << OFFSET_Y <<  " " << OFFSET_Z << std::endl;
    iniFile.endGroup();

    iniFile.beginGroup("REGION_OF_INTEREST");
    ROI_ENABLE = iniFile.value("ROI_ENABLE", false).toBool();
    P_0_X = iniFile.value("P_0_X", 0.0).toDouble();
    P_0_Y = iniFile.value("P_0_Y", 0.0).toDouble();
    P_0_Z = iniFile.value("P_0_Z", 0.0).toDouble();

    P_1_X = iniFile.value("P_1_X", 0.0).toDouble();
    P_1_Y = iniFile.value("P_1_Y", 0.0).toDouble();
    P_1_Z = iniFile.value("P_1_Z", 0.0).toDouble();

    P_2_X = iniFile.value("P_2_X", 0.0).toDouble();
    P_2_Y = iniFile.value("P_2_Y", 0.0).toDouble();
    P_2_Z = iniFile.value("P_2_Z", 0.0).toDouble();

    P_3_X = iniFile.value("P_3_X", 0.0).toDouble();
    P_3_Y = iniFile.value("P_3_Y", 0.0).toDouble();
    P_3_Z = iniFile.value("P_3_Z", 0.0).toDouble();

    std::cout << "ROI_ENABLE " << (int)ROI_ENABLE << std::endl;
    std::cout << "ROI P_0 " << P_0_X << " " << P_0_Y <<  " " << P_0_Z << std::endl;
    std::cout << "ROI P_1 " << P_1_X << " " << P_1_Y <<  " " << P_1_Z << std::endl;
    std::cout << "ROI P_2 " << P_2_X << " " << P_2_Y <<  " " << P_2_Z << std::endl;
    std::cout << "ROI P_3 " << P_3_X << " " << P_3_Y <<  " " << P_3_Z << std::endl;
    iniFile.endGroup();

    iniFile.beginGroup("CUBES_TRACKER_OFFSET_TO_ROBOT");
    cubes_robotOffset.x = iniFile.value("X", 0.0).toDouble();
    cubes_robotOffset.y = iniFile.value("Y", 0.0).toDouble();
    cubes_robotOffset.z = iniFile.value("Z", 0.0).toDouble();
    std::cout << "cubes_robotOffset X, Y Z " << cubes_robotOffset.x << " " << cubes_robotOffset.y << " " << cubes_robotOffset.z << std::endl;
    iniFile.endGroup();

    iniFile.beginGroup("ROBOT_SAFTEY_RADIUS_CUBES");
    cubes_robotSafety_min = iniFile.value("MIN",300.0).toDouble();
    cubes_robotSafety_max = iniFile.value("MAX", 700.0).toDouble();
    std::cout << "cubes_robotSafety_min cubes_robotSafety_max " << cubes_robotSafety_min << " " << cubes_robotSafety_max << std::endl;
    iniFile.endGroup();


}



void Detector::standBy()
{
    if(updateInputImg())
    {
        checkCalibration();
        //        checkROI();
        mOutputImg = mInputImg;
    }
}


void Detector::detectObjects()
{
    //std::cout << "detectObjects" << std::endl;
    if(updateInputImg())
    {
        //std::cout << "detecting" << std::endl;

        preProcess();

        updateColourSegmentedImg();

        updateCountourImage();

        if(ROI_ENABLE)
            checkROI();

        updateOutputImg();
    }
}

bool Detector::updateInputImg()
{

    if(mSub->getImageData(mInputImg))
        return true;
    else
        return false;
}

void Detector::preProcess()
{
    cv::cvtColor(mInputImg, mHSVImg, CV_BGR2HSV);
}

void Detector::updateColourSegmentedImg()
{

    uchar h, s;

    if(debugSeg)
    {
        mColourSegmentedImg.setTo(cv::Scalar(0,0,0));
    }

    uchar lowerThreshold[4];
    uchar upperThreshold[4];
    for(unsigned int i = 0; i < mHThresholds.size(); ++i)
    {
        targetImgVec[i].setTo(cv::Scalar(0,0,0));
        lowerThreshold[i] = static_cast<uchar>(mHThresholds[i][0]);
        upperThreshold[i] = static_cast<uchar>(mHThresholds[i][1]);
    }

    int width = mColourSegmentedImg.size().width;
    int height = mColourSegmentedImg.size().height;


    for(int i=0;i<pixelVec.size();++i)
    {
        static int x, y;
        x = pixelVec[i].x;
        y = pixelVec[i].y;

        h = mHSVImg.at<Vec3b>(y, x)[0];
        s = mHSVImg.at<Vec3b>(y, x)[1];

        for(unsigned int i = 0; i < mHThresholds.size(); ++i)
        {
            if(TARGET_COLOUR_ENABLE[i])
            {

                if(h > lowerThreshold[i] && h < upperThreshold[i] && s > 120)
                {
                    //ptr_target[i][x] = 255;

                    targetImgVec[i].at<uchar>(y,x) = 255;

                    if(debugSeg)
                    {
                        mColourSegmentedImg.at<Vec3b>(y,x) = TARGET_COLOUR_CODE[i];
                    }
                }
            }
        }
    }

    setColourSegmentedImg(mColourSegmentedImg);
}

void Detector::updateCountourImage()
{

    mContourDispImg = mInputImg;
    int target_count = 0;
    ros_tum_msgs::ActorVec objDataContainer;
    util::Util::clearActorsDataContainer(objDataContainer);
    for(unsigned int i = 0; i < targetImgVec.size(); ++i)
    {
        if(TARGET_COLOUR_ENABLE[i])
        {
            mContourImg = targetImgVec[i];
            erode(mContourImg, mTmpImg, Mat());
            dilate(mTmpImg, mContourImg, Mat());

            dilate(mContourImg, mTmpImg, Mat());
            erode(mTmpImg, mContourImg, Mat());

            std::vector<std::vector<Point> > contours;
            std::vector<Vec4i> hierarchy;
            findContours( mContourImg, contours, hierarchy,
                          CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

            //std::cout << "contours " << i << " " << contours.size() << std::endl;

            if(contours.size() > 0)
            {
                int idx = 0;
                for( ; idx >= 0; idx = hierarchy[idx][0] )
                {
                    //Scalar color( rand()&255, rand()&255, rand()&255 );

                    //std::cout << "contours " << i << " " << contours.size() << std::endl;
                    double contArea = contourArea(contours[idx]);

                    if(contArea > 500 && contArea < 7500)
                    {
                        RotatedRect rotRect = minAreaRect(contours[idx]);

                        //drawContours( mContourDispImg, contours, idx, Scalar( 0,255,0 ), 1, 8, hierarchy );
                        //std::cout<< "Contour " << idx << " Area: " << contourArea(contours[idx]) << std::endl;
                        double x	    = rotRect.center.x;
                        double y 		= rotRect.center.y;
                        double width 	= rotRect.size.width;
                        double height 	= rotRect.size.height;
                        double angle     = rotRect.angle;

                        double max = std::max(rotRect.size.width, rotRect.size.height);
                        double min = std::min(rotRect.size.width, rotRect.size.height);

                        if(min > 0)
                        {
                            double frac=max/min;
                            //std::cout << "frac " << frac << std::endl;
                            //if(frac > 1.1 && frac < 1.9)
                            //{
                            //std::cout << rotRect.size.width << " " << rotRect.size.height << std::endl;
                            static cv::Point3d point3D;
                            static cv::Point2d point2d;
                            point2d.x=x;
                            point2d.y=y;
                            static double z3d = 0.0;

                            getScreenTo3DPoints(point2d, point3D, z3d);

                            //std::cout << "point3D " << point3D.x << " " << point3D.y << " " << point3D.z << std::endl;

                            objDataContainer.ActorVec.push_back(ros_tum_msgs::Actor());
                            objDataContainer.ActorVec.back().targetPoseVec.resize(1);
                            objDataContainer.ActorVec.back().targetPoseVec[0].position.x = point3D.x+OFFSET_X;
                            objDataContainer.ActorVec.back().targetPoseVec[0].position.y = point3D.y+OFFSET_Y+5.0;
                            objDataContainer.ActorVec.back().targetPoseVec[0].position.z = 210.0;//z3d+OFFSET_Z;
                            objDataContainer.ActorVec.back().targetPoseVec[0].orientation.x = 0.0;
                            objDataContainer.ActorVec.back().targetPoseVec[0].orientation.y = 0.0;
                            objDataContainer.ActorVec.back().targetPoseVec[0].orientation.z = angle;
                            objDataContainer.ActorVec.back().targetPoseVec[0].orientation.w = 1.0;
                            objDataContainer.ActorVec.back().targetType = "BOX";
                            objDataContainer.ActorVec.back().timeStamp = QTime::currentTime().toString().toStdString();
                            objDataContainer.ActorVec.back().targetId = target_count;

                            Scalar color;
                            objDataContainer.ActorVec.back().targetProperty = TARGET_COLOUR_NAMES[i];
                            target_count++;
                            color = Scalar( TARGET_COLOUR_CODE[i][0], TARGET_COLOUR_CODE[i][1], TARGET_COLOUR_CODE[i][2] );

                            cv::circle(mContourDispImg, cv::Point(x,y), width/2.0, color, 3);
                            //}
                        }
                        //std::cout<< "Contour " << idx << " Area: " << contourArea(contours[idx]) << std::endl;

                    }
                }

            }

        }

    }

    mPub->setActorsData(objDataContainer);

}


void Detector::computeTragetsBoundingBox()
{

}

void Detector::compute3DPosition()
{

}

void Detector::updateTargetContainer()
{

}

void Detector::updateOutputImg()
{
    mOutputImgMutex.lock();
    mOutputImg = mContourDispImg;
    mOutputImgMutex.unlock();
}

void Detector::initCalibrationdata()
{
    ros_tum_msgs::CameraCalibData data;
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ros_tum_msgs::CameraInfo>(CAMERA_INFO_SERVICE_NAME);
    ros_tum_msgs::CameraInfo srv;
    if (client.call(srv))
    {
        mWidth=srv.response.response.width;
        mHeight=srv.response.response.height;

        std::cout << "mWidth  mHeight from service " << mWidth << " " << mHeight << std::endl;

        intrinsicsMat=cv::Mat(3,3,DataType<double>::type);
        std::cout << "intrinsicsMat from service " << std::endl;
        double *input = (double*)(intrinsicsMat.data);
        for(int i=0;i<9;++i)
        {
            input[i]=srv.response.response.K[i];
        }
        std::cout << "intrinsicsMat " << intrinsicsMat << std::endl;

        extrinsicsMat=cv::Mat(4,4,DataType<double>::type);
        std::cout << "extrinsicsMat from service " << std::endl;
        double *input1 = (double*)(extrinsicsMat.data);
        for(int i=0;i<16;++i)
        {
            input1[i]=srv.response.response.E[i];
        }
        std::cout << "extrinsicsMat " << extrinsicsMat << std::endl;

        projectionMat=cv::Mat(3,4,DataType<double>::type);
        std::cout << "projectionMat from service " << std::endl;
        double *input2 = (double*)(projectionMat.data);
        for(int i=0;i<12;++i)
        {
            input2[i]=srv.response.response.P[i];

        }
        std::cout << "projectionMat " << projectionMat << std::endl;

    }
    else
    {
        ROS_ERROR("Failed to call service CAMERA_0_INFO");
        throw;
    }

}

void Detector::checkCalibration()
{

    cv::Point3d worldPoint;
    worldPoint.x = 0.0;
    worldPoint.y = 0.0;
    worldPoint.z = 0.0;
    cv::Point2i  imgPoint;

    get3DToScreenPoints(worldPoint, imgPoint);

    cv::circle(mInputImg, imgPoint, 3, Scalar(0, 255, 0));


    cv::Point3d worldPoint1;
    worldPoint1.x = 200.0;
    worldPoint1.y = 0.0;
    worldPoint1.z = 0.0;
    cv::Point2i  imgPoint1;

    get3DToScreenPoints(worldPoint1, imgPoint1);

    cv::circle(mInputImg, imgPoint1, 3, Scalar(255, 0, 0));

    cv::Point3d worldPoint2;
    worldPoint2.x = 0.0;
    worldPoint2.y = 200.0;
    worldPoint2.z = 0.0;
    cv::Point2i  imgPoint2;

    get3DToScreenPoints(worldPoint2, imgPoint2);

    cv::circle(mInputImg, imgPoint2, 3, Scalar(0, 0, 255));

}

void Detector::checkROI()
{
    if(ROI_ENABLE)
    {
        static cv::Point3d p0;
        static cv::Point3d p1;
        static cv::Point3d p2;
        static cv::Point3d p3;

        p0.x = P_0_X;
        p0.y = P_0_Y;
        p0.z = P_0_Z;

        p1.x = P_1_X;
        p1.y = P_1_Y;
        p1.z = P_1_Z;

        p2.x = P_2_X;
        p2.y = P_2_Y;
        p2.z = P_2_Z;

        p3.x = P_3_X;
        p3.y = P_3_Y;
        p3.z = P_3_Z;

        static cv::Point2i ps0;
        static cv::Point2i ps1;
        static cv::Point2i ps2;
        static cv::Point2i ps3;

        get3DToScreenPoints(p0, ps0);
        get3DToScreenPoints(p1, ps1);
        get3DToScreenPoints(p2, ps2);
        get3DToScreenPoints(p3, ps3);

        cv::line(mInputImg, ps0, ps1, Scalar(0, 255, 0), 3);
        cv::line(mInputImg, ps1, ps2, Scalar(0, 255, 0), 3);
        cv::line(mInputImg, ps2, ps3, Scalar(0, 255, 0), 3);
        cv::line(mInputImg, ps3, ps0, Scalar(0, 255, 0), 3);

    }
    else
    {
        cv::Point2i ps0;
        cv::Point2i ps1;

        ps0.x = 0;
        ps0.y = 0;

        ps1.x = mInputImg.size().width;
        ps1.y = mInputImg.size().height;

        cv::rectangle(mInputImg, ps0, ps1, Scalar(0, 255, 0), 2);
    }
}



bool Detector::insidePolygon(cv::Point2i *polygon, int N, cv::Point2i p)
{
    int counter = 0;
    int i;
    double xinters;
    Point p1,p2;

    p1 = polygon[0];
    for (i=1;i<=N;i++) {
        p2 = polygon[i % N];
        if (p.y > std::min(p1.y,p2.y)) {
            if (p.y <= std::max(p1.y,p2.y)) {
                if (p.x <= std::max(p1.x,p2.x)) {
                    if (p1.y != p2.y) {
                        xinters = (p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
                        if (p1.x == p2.x || p.x <= xinters)
                            counter++;
                    }
                }
            }
        }
        p1 = p2;
    }

    if (counter % 2 == 0)
        return false;
    else
        return true;
}

void Detector::getScreenTo3DPoints(const cv::Point2i& screenPoint, cv::Point3d& point3D, double z)
{
    static double fx = intrinsicsMat.at<double>(0,0);
    static double fy = intrinsicsMat.at<double>(1,1);
    static double cx = intrinsicsMat.at<double>(0,2);
    static double cy = intrinsicsMat.at<double>(1,2);

    static double r11 = extrinsicsMat.at<double>(0,0);
    static double r12 = extrinsicsMat.at<double>(0,1);
    static double r13 = extrinsicsMat.at<double>(0,2);
    static double r21 = extrinsicsMat.at<double>(1,0);
    static double r22 = extrinsicsMat.at<double>(1,1);
    static double r23 = extrinsicsMat.at<double>(1,2);
    static double r31 = extrinsicsMat.at<double>(2,0);
    static double r32 = extrinsicsMat.at<double>(2,1);
    static double r33 = extrinsicsMat.at<double>(2,2);

    static double px = extrinsicsMat.at<double>(0,3);
    static double py = extrinsicsMat.at<double>(1,3);
    static double pz = extrinsicsMat.at<double>(2,3);

    static double Xs;
    static double Ys;

    //z=0.0;
    //std::cout << "z " << z << std::endl;
    Xs = screenPoint.x;
    Ys = screenPoint.y;
    point3D.x = ((cx*r32 - Xs*r32 + fx*r12)*(cy*pz - Ys*pz + cy*r33 + fy*py + fy*r23 - Ys*z*r33))/(Xs*fy*r21*r32 - Xs*fy*r22*r31 - Ys*fx*r11*r32 + Ys*fx*r12*r31 + cy*fx*r11*r32 - cy*fx*r12*r31 - cx*fy*r21*r32 + cx*fy*r22*r31 + fx*fy*r11*r22 - fx*fy*r12*r21) - ((cy*r32 - Ys*r32 + fy*r22)*(cx*pz - Xs*pz + cx*r33 + fx*px + fx*r13 - Xs*z*r33))/(Xs*fy*r21*r32 - Xs*fy*r22*r31 - Ys*fx*r11*r32 + Ys*fx*r12*r31 + cy*fx*r11*r32 - cy*fx*r12*r31 - cx*fy*r21*r32 + cx*fy*r22*r31 + fx*fy*r11*r22 - fx*fy*r12*r21);
    point3D.y = ((cy*r31 - Ys*r31 + fy*r21)*(cx*pz - Xs*pz + cx*r33 + fx*px + fx*r13 - Xs*z*r33))/(Xs*fy*r21*r32 - Xs*fy*r22*r31 - Ys*fx*r11*r32 + Ys*fx*r12*r31 + cy*fx*r11*r32 - cy*fx*r12*r31 - cx*fy*r21*r32 + cx*fy*r22*r31 + fx*fy*r11*r22 - fx*fy*r12*r21) - ((cx*r31 - Xs*r31 + fx*r11)*(cy*pz - Ys*pz + cy*r33 + fy*py + fy*r23 - Ys*z*r33))/(Xs*fy*r21*r32 - Xs*fy*r22*r31 - Ys*fx*r11*r32 + Ys*fx*r12*r31 + cy*fx*r11*r32 - cy*fx*r12*r31 - cx*fy*r21*r32 + cx*fy*r22*r31 + fx*fy*r11*r22 - fx*fy*r12*r21);
    point3D.z = z;

}

void Detector::get3DToScreenPoints(const cv::Point3d& point3D, cv::Point2i& screenPoint)
{

    static cv::Mat point(4, 1, DataType<double>::type);
    static cv::Mat screen(3, 1, DataType<double>::type);
    point.at<double>(0, 0) = point3D.x;
    point.at<double>(1, 0) = point3D.y;
    point.at<double>(2, 0) = point3D.z;
    point.at<double>(3, 0) = 1.0;

    screen = projectionMat * point;

    screenPoint.x = static_cast<int>(screen.at<double>(0, 0) / screen.at<double>(2, 0));
    screenPoint.y = static_cast<int>(screen.at<double>(1, 0) / screen.at<double>(2, 0));

}

void Detector::generatePixelVecForROI()
{
    if(ROI_ENABLE)
    {
        pixelVec.clear();

        cv::Point3d p0;
        cv::Point3d p1;
        cv::Point3d p2;
        cv::Point3d p3;

        p0.x = P_0_X;
        p0.y = P_0_Y;
        p0.z = P_0_Z;

        p1.x = P_1_X;
        p1.y = P_1_Y;
        p1.z = P_1_Z;

        p2.x = P_2_X;
        p2.y = P_2_Y;
        p2.z = P_2_Z;

        p3.x = P_3_X;
        p3.y = P_3_Y;
        p3.z = P_3_Z;

        cv::Point2i ps0;
        cv::Point2i ps1;
        cv::Point2i ps2;
        cv::Point2i ps3;

        get3DToScreenPoints(p0, ps0);
        get3DToScreenPoints(p1, ps1);
        get3DToScreenPoints(p2, ps2);
        get3DToScreenPoints(p3, ps3);


        int x_min = std::min(ps0.x, std::min(ps1.x, std::min(ps2.x, ps3.x)));
        int y_min = std::min(ps0.y, std::min(ps1.y, std::min(ps2.y, ps3.y)));

        int x_max = std::max(ps0.x, std::max(ps1.x, std::max(ps2.x, ps3.x)));
        int y_max = std::max(ps0.y, std::max(ps1.y, std::max(ps2.y, ps3.y)));

        cv::Point2i polyPoints[5];
        polyPoints[0] = ps0;
        polyPoints[1] = ps1;
        polyPoints[2] = ps2;
        polyPoints[3] = ps3;
        polyPoints[4] = ps0;

        for(int x=0;x<mInputImg.size().width;++x)
        {
            for(int y=0;y<mInputImg.size().height;++y)
            {
                if(insidePolygon(polyPoints, 4, cv::Point2i(x, y)))
                {
                    pixelVec.push_back(cv::Point2i(x, y));
                }
            }
        }
    }
    else
    {
        for(int x=0;x<mInputImg.size().width;++x)
        {
            for(int y=0;y<mInputImg.size().height;++y)
            {
                pixelVec.push_back(cv::Point2i(x, y));
            }
        }
    }
}

}


