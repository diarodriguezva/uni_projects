#include <camera/ConfigData.h>
#include <ros/package.h>

using namespace std;

ConfigData::ConfigData()
{

}

ConfigData::~ConfigData()
{

}

void ConfigData::parse()
{
	
    QString filename((ros::package::getPath("camera") + "/config/config.ini").c_str());
    QFileInfo config(filename);

    if(!config.exists())
    {
        std::cout<<"error reading config.ini file"<<std::endl;
        throw;
    }

    QSettings iniFile(filename, QSettings::IniFormat);

    iniFile.beginGroup("CAMERA");
    CAM_ID = iniFile.value("CAM_ID", 0).toInt();
    CAMERA_IMAGE_TOPIC_NAME = iniFile.value("CAMERA_IMAGE_TOPIC_NAME", "").toString().toStdString();
    CAMERA_INFO_SERVICE_NAME = iniFile.value("CAMERA_INFO_SERVICE_NAME", "").toString().toStdString();
    SHOW_DISPLAY = iniFile.value("SHOW_DISPLAY", false).toBool();
    std::cout << "CAM_ID " << CAM_ID << std::endl;
    std::cout << "CAMERA_IMAGE_TOPIC_NAME " << CAMERA_IMAGE_TOPIC_NAME << std::endl;
    std::cout << "CAMERA_INFO_SERVICE_NAME " << CAMERA_INFO_SERVICE_NAME << std::endl;
    std::cout << "SHOW_DISPLAY " << (int)SHOW_DISPLAY << std::endl;
    iniFile.endGroup();
    
}

