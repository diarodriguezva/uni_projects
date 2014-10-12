/** BEGIN LICENCE ************************************************************/
/* Copyright 2011-2012 TUM-fortiss                    		             */
/* All Rights Reserved.                                                      */
/* Contact author: Suraj Nair                                                */
/* E-mail: nair@fortiss.org, nair@in.tum.de	                             */
/* If you have any questions regarding this agreement or the licensing of    */
/* this technology, please send them to the contact author above.            */
/*                                                                           */
/* Author(s):                                                                */
/* Suraj Nair nair@fortiss.org, nair@in.tum.de	                             */
/** END LICENCE **************************************************************/


#ifndef ACTORSPUBLISHER_H_
#define ACTORSPUBLISHER_H_

#include <QThread>
#include <QMutex>
#include <comm_lib/CommonDefs.h>
#include <comm_lib/util/Util.h>
#include <actor_msgs/ActorVec.h>

using namespace std;
using namespace util;

namespace comminterface
{

/**
 * @brief Class for ROS Actors Publisher
 * @author Suraj Nair nair@fortiss.org, nair@in.tum.de
 */
class ActorsPublisher : public QThread
{

public:

    /**
     * @brief Default Constructor
     *
     * @param topicName Name of Topic to be published
     */
    ActorsPublisher(const std::string& topicName);

    /**
     * @brief Destructor
     *
     */
    virtual ~ActorsPublisher();

    /**
     * @brief Thread run
     *
     */
    virtual void run();

    /**
     * @brief Method to stop thread run
     *
     */
    void stopThread()
    {
        runThread = false;
    }

    /**
     * @brief Method to set Actors Data
     *
     * @param data Actors Container
     */
    void setActorsData(const actor_msgs::ActorVec& data);

    /**
     * @brief Method to get Actors data
     *
     * @param data Actors Container
     */
    void getActorsData(actor_msgs::ActorVec& data);

    /**
     * @brief Method to set thread loop rate
     *
     * @param rate Loop rate (msecs)
     */
    void setLoopRate(unsigned int rate);

public:

    bool runThread; /**< Thread Run Flag */

    unsigned int mLoopRate; /**< Thread Loop Rate */

    std::string mTopicName; /**< Topic Name Published */

    QMutex mActorsDataMutex; /**< Actors Data Mutex  */
    actor_msgs::ActorVec mActorsData; /**< Actors Data Container  */

    ros::Publisher _pub; /**< ROS Publisher */
};

};

#endif /*ACTORSPUBLISHER_H_*/

