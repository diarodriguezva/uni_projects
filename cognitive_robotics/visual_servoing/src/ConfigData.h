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

        std::string VS_TARGET_TOPIC_NAME;

};

#endif

