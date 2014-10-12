#include "ConfigData.h"

using namespace std;

ConfigData::ConfigData()
{

}

ConfigData::~ConfigData()
{

}

void ConfigData::parse()
{
    QString filename("config.ini");
    QFileInfo config(filename);

    if(!config.exists())
    {
        std::cout<<"error reading config.ini file"<<std::endl;
        throw;
    }

    QSettings iniFile(filename, QSettings::IniFormat);

    iniFile.beginGroup("TARGET_SUBSCRIBER");
    VS_TARGET_TOPIC_NAME = iniFile.value("VS_TARGET_TOPIC_NAME", "").toString().toStdString();
    std::cout << "TARGET_PUBLISHER VS_TARGET_TOPIC_NAME " << VS_TARGET_TOPIC_NAME << std::endl;
    iniFile.endGroup();
}

