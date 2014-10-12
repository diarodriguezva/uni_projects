#include "Tracker.h"

namespace tracking1
{

Tracker::Tracker()
{

    init();

}

Tracker::~Tracker()
{

    mInImg.release();
    mHSVImg.release();
    mOutputImg.release();

    for (int i = 0; i < mBins; ++i) {
        mTarget.histogram[i].erase(mTarget.histogram[i].begin(), mTarget.histogram[i].end());
        mCurrentHistogram[i].erase(mCurrentHistogram[i].begin(), mCurrentHistogram[i].end());
    }

    mPub->stopThread();
    delete mPub;

    mSub->stopThread();
    delete mSub;


    mTargetVec.ActorVec.erase(mTargetVec.ActorVec.begin(), mTargetVec.ActorVec.end());
}

void Tracker::parseConifgFile()
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

    iniFile.beginGroup("TARGET_PUBLISHER");
    VS_TARGET_TOPIC_NAME = iniFile.value("VS_TARGET_TOPIC_NAME", "").toString().toStdString();
    std::cout << "TARGET_PUBLISHER VS_TARGET_TOPIC_NAME " << VS_TARGET_TOPIC_NAME << std::endl;
    iniFile.endGroup();

    iniFile.beginGroup("DEBUG");
    PRINT_AVG_LIKELIHOOD = iniFile.value("PRINT_AVG_LIKELIHOOD", "false").toBool();
    PRINT_MAX_LIKELIHOOD = iniFile.value("PRINT_MAX_LIKELIHOOD", "false").toBool();
    PRINT_PARTICLE_LIKELIHOOD = iniFile.value("PRINT_PARTICLE_LIKELIHOOD", "false").toBool();
    DRAW_PARTICLES = iniFile.value("DRAW_PARTICLES", "false").toBool();
    std::cout << "DEBUG PRINT_AVG_LIKELIHOOD " << PRINT_AVG_LIKELIHOOD << std::endl;
    std::cout << "DEBUG PRINT_MAX_LIKELIHOOD " << PRINT_MAX_LIKELIHOOD << std::endl;
    std::cout << "DEBUG PRINT_PARTICLE_LIKELIHOOD " << PRINT_PARTICLE_LIKELIHOOD << std::endl;
    std::cout << "DEBUG DRAW_PARTICLES " << DRAW_PARTICLES << std::endl;
    iniFile.endGroup();

}


void Tracker::init()
{
    parseConifgFile();

    ros_tum_msgs::CameraCalibData data;
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ros_tum_msgs::CameraInfo>(CAMERA_INFO_SERVICE_NAME);
    ros_tum_msgs::CameraInfo srv;
    if (client.call(srv))
    {
        mWidth=srv.response.response.width;
        mHeight=srv.response.response.height;

        std::cout << "mWidth  mHeight from service " << mWidth << " " << mHeight << std::endl;
    }
    else
    {
        ROS_ERROR("Failed to call service CAMERA_INFO_SERVICE_NAME");
        std::cout << CAMERA_INFO_SERVICE_NAME << std::endl;
        throw;
    }

    mInImg=cv::Mat(cv::Size(mWidth, mHeight), CV_8UC3);
    mHSVImg=cv::Mat(cv::Size(mWidth, mHeight), CV_8UC3);


    mBins=10;
    mTarget.x_dim=50;
    mTarget.y_dim=100;


    mTarget.histogram.resize(mBins);
    mCurrentHistogram.resize(mBins);

    for (int i = 0; i < mBins; ++i) {
        mTarget.histogram[i].resize(mBins);
        mCurrentHistogram[i].resize(mBins);
    }

    double mulFactX_lut = (double)((mBins-1) /255.0);
    for(unsigned int x = 0; x < 256; ++x)
    {
        lut_1[x] = static_cast<unsigned int>(mulFactX_lut*x);
    }


    cv::Mat refImg = cv::imread("Target.bmp");
    cv::Mat refImgHSV=refImg;
    cv::cvtColor(refImg, refImgHSV, CV_BGR2HSV);
    computeRefHistogram(refImgHSV);

    refImg.release();
    refImgHSV.release();

    cv::Vec3d pose(320, 240, 1.0);
    mFilter.initialize(pose);

    mSub = new comminterface::RosImageSubscriber(CAMERA_IMAGE_TOPIC_NAME);
    mSub->start();

    mPub = new comminterface::RosActorsPublisher(VS_TARGET_TOPIC_NAME);
    mPub->start();

    mTargetVec.ActorVec.push_back(ros_tum_msgs::Actor());
    mTargetVec.ActorVec.back().targetPoseVec.resize(1);
    mTargetVec.ActorVec.back().targetType = "BALL";
    mTargetVec.ActorVec.back().targetProperty = "RED";
    mTargetVec.ActorVec.back().timeStamp = QTime::currentTime().toString().toStdString();
    mTargetVec.ActorVec.back().targetId = 0;

}


void Tracker::computeRefHistogram(cv::Mat& input)
{

    std::cout<<"computeHistogram"<<std::endl;

    for (int i = 0; i < mBins; ++i) {
        for (int j = 0; j < mBins; ++j)
        {
            mTarget.histogram[i][j]=0.0;
        }
    }


    uchar h, s, v;

    double pixelCount = 0.0f;

    //Collect Histogram

    for(int x = 0; x < input.size().width; ++x)
    {
        for(int y = 0; y < input.size().height; ++y)
        {

            h = input.at<cv::Vec3b>(y, x)[0];
            s = input.at<cv::Vec3b>(y, x)[1];
            v = input.at<cv::Vec3b>(y, x)[2];

            if(v != 0)
            {
                mTarget.histogram[ lut_1[h] ] [ lut_1[s] ]++;
                pixelCount+= 1.0;
            }
        }
    }

    //Normalize Histogram
    if(pixelCount > 10.0)
    {
        std::cout << "Histogram " << std::endl;
        for (int i = 0; i < mBins; ++i) {
            for (int j = 0; j < mBins; ++j)
            {
                mTarget.histogram[i][j]  /= pixelCount;

                std::cout << mTarget.histogram[i][j] << " ";
            }
            std::cout << "\n";
        }
    }


}

bool Tracker::process()
{

    if(mSub->getImageData(mInImg))
    {
        cv::cvtColor(mInImg, mHSVImg, CV_BGR2HSV);

        //cv::imshow("hsv", mHSVImg);

        return true;
    }
    else
    {
        return false;
    }


}

double Tracker::computeLikelihood(cv::Mat& input, cv::Vec3d& pose)
{

    //std::cout<<"computeHistogram"<<std::endl;

    for (int i = 0; i < mBins; ++i) {
        for (int j = 0; j < mBins; ++j)
        {
            mCurrentHistogram[i][j]=0.0;
        }
    }


    uchar h, s, v;

    double pixelCount = 0.0f;

    //Collect Histogram

    static int mWidth_2 = mWidth / 2;
    static int mHeight_2 = mHeight /2;
    static int x_dim_2 = mTarget.x_dim / 2;
    static int y_dim_2 = mTarget.y_dim / 2;

    int x_min = std::max(0,  (int)((pose[0] ) - (pose[2]*x_dim_2)));
    int y_min = std::max(0, (int)((pose[1] ) - (pose[2]*y_dim_2)));
    int x_max = std::min(mWidth, (int)((pose[0] ) + (pose[2]*x_dim_2)));
    int y_max = std::min(mHeight, (int)((pose[1] ) + (pose[2]*y_dim_2)));


    //std::cout << "image " << x_min << " " << x_max << " " << y_min << " " << y_max << std::endl;

    for(int x = x_min; x < x_max; ++x)
    {
        for(int y = y_min; y < y_max; ++y)
        {

            h = mHSVImg.at<cv::Vec3b>(y, x)[0];
            s = mHSVImg.at<cv::Vec3b>(y, x)[1];
            v = mHSVImg.at<cv::Vec3b>(y, x)[2];

            if(v != 0)
            {
                mCurrentHistogram[ lut_1[h] ] [ lut_1[s] ]++;
                pixelCount+= 1.0;
            }
        }
    }

    //std::cout << "pixelCount " << pixelCount << std::endl;

    //Normalize Histogram
    if(pixelCount > 10.0)
    {
        //std::cout << "Histogram " << std::endl;
        for (int i = 0; i < mBins; ++i) {
            for (int j = 0; j < mBins; ++j)
            {
                mCurrentHistogram[i][j]  /= pixelCount;

                //std::cout << mCurrentHistogram[i][j] << " ";
            }
            //std::cout << "\n";
        }
    }

    //compute bhattacharya distance

    static double dist;
    dist=computeBhattDist(mCurrentHistogram, mTarget.histogram);

    //std::cout << "dist " << dist << std::endl;
    static double lambda=mFilter.getLambda();
    static double likelhood;
    likelhood = exp(-0.5*dist*dist*lambda);

    //    if(likelhood > 0.05)
    //        std::cout << "likelihood " << likelhood << std::endl;


    return likelhood;
}


double Tracker::computeBhattDist(Histogram2D& hist, Histogram2D& refHist)
{
    //Compute bhattacharya distance between hist and refHist
    static double bhattDist;
    bhattDist = 0.0;

    for (int i = 0; i < mBins; ++i) {
        for (int j = 0; j < mBins; ++j)
        {
            if(hist[i][j] !=  0 && refHist[i][j] != 0)
            {
                bhattDist += sqrt(hist[i][j] * refHist[i][j]);
            }
        }
    }

    return sqrt(1.0 - sqrt(bhattDist));

}


void Tracker::trackNext1()
{

    if(process())
    {

        mFilter.predict();
        static cv::Vec3d poseData;
        static double likelihood;
        for (int i=0;i<mFilter.nOfParticles(); i++)
        {
            mFilter.getParticlePose(i, poseData);

            likelihood=computeLikelihood(mHSVImg, poseData);

            mFilter.setParticleWeight(i, likelihood);

            //            static cv::Scalar color_1(255,255,255);
            //            drawPose(poseData, color_1);
            //            cv::imshow("tmp", mInImg);
            //            cv::waitKey(10);

            if(PRINT_PARTICLE_LIKELIHOOD)
            {
                std::cout << "Particle " << i << " " << "Likelihood " << likelihood << std::endl;
            }

            if(DRAW_PARTICLES)
            {
                static cv::Scalar color1(255,255,255);
                drawPose(poseData, color1, 1);
            }
        }
        mFilter.correct();
        mFilter.getOutputPose(poseData);

        if(PRINT_AVG_LIKELIHOOD)
        {
            std::cout << "Avg Likelihood " << mFilter.getAvgLikelihood() << std::endl;
        }

        if(PRINT_MAX_LIKELIHOOD)
        {
            std::cout << "Max Likelihood " << mFilter.getMaxLikelihood() << std::endl;
        }

        static bool targetOK;
        targetOK=false;
        if(mFilter.isReInitEnable())
        {
            if(mFilter.getAvgLikelihood() > mFilter.getReInitThreshold())
            {
                targetOK=true;
            }
            else
            {
                std::cout << "Re init tracker" << std::endl;
                poseData[0]=320.0;
                poseData[1]=240.0;
                poseData[2]=1.0;
                mFilter.reinit(poseData);
                targetOK=false;
            }
        }
        else
        {
            targetOK=true;
        }

        if(targetOK)
        {
            //std::cout << "pose " << poseData[0] << " " << poseData[1] << " " << poseData[2] << std::endl;
            static cv::Scalar color(0,255,0);
            drawPose(poseData, color, 3);

            mTargetVec.ActorVec.back().targetPoseVec[0].position.x = poseData[0];
            mTargetVec.ActorVec.back().targetPoseVec[0].position.y = poseData[1];
            mTargetVec.ActorVec.back().targetPoseVec[0].position.z = poseData[2];
            mTargetVec.ActorVec.back().targetPoseVec[0].orientation.x = 0.0;
            mTargetVec.ActorVec.back().targetPoseVec[0].orientation.y = 0.0;
            mTargetVec.ActorVec.back().targetPoseVec[0].orientation.z = 0.0;
            mTargetVec.ActorVec.back().targetPoseVec[0].orientation.w = 1.0;
            mTargetVec.ActorVec.back().timeStamp = QTime::currentTime().toString().toStdString();
            mPub->setActorsData(mTargetVec);
        }

        setOutputImg();


    }
    else
    {
        //std::cout << "No image" << std::endl;
        setOutputImg();
    }
}

void Tracker::getPose(cv::Vec3d& pose)
{

}

void Tracker::drawPose(cv::Vec3d& pose, cv::Scalar& color, int lineSize)
{

    static int mWidth_2 = mWidth / 2;
    static int mHeight_2 = mHeight /2;
    static int x_dim_2 = mTarget.x_dim / 2;
    static int y_dim_2 = mTarget.y_dim / 2;
    cv::Point center;
    center.x=pose[0];
    center.y=pose[1];
    int radius = pose[2]*mTarget.x_dim;

    //std::cout << "circle " << center.x << " " << center.y << " " << radius << std::endl;
    //cv::circle(mInImg, center, radius, color, 3);

    cv::rectangle(mInImg, cv::Rect(center.x-x_dim_2, center.y-y_dim_2, mTarget.x_dim, mTarget.y_dim ), color, lineSize);

}

void Tracker::setOutputImg()
{
    mOutputImg=mInImg;
}
void Tracker::getOutputImage(cv::Mat& img)
{
    img=mOutputImg;
}


}
