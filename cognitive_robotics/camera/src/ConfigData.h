/*
* Tracking
* started by Suraj Nair
*/
#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <exception>
#include <stdexcept>
#include <assert.h>
#include <iostream>
#include <QString>
#include <QFileInfo>
#include <QSettings>

using namespace std;

class ConfigData
{
public:

    ConfigData();
    ~ConfigData();

    void parse();

public:

    int CAM_ID;
    std::string CAMERA_IMAGE_TOPIC_NAME;
    std::string CAMERA_INFO_SERVICE_NAME;
    bool SHOW_DISPLAY;


};

#endif

