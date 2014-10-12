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


#ifndef ACTORSSUBSCRIBER_H_
#define ACTORSSUBSCRIBER_H_

#include "CommonDefs.h"
#include "actor_msgs/ActorVec.h"
#include <sstream>

using namespace std;

namespace comminterface
{
/**
 * @brief Class for ROS Actors Subscriber
 * @author Suraj Nair nair@fortiss.org, nair@in.tum.de
 */
class ActorsSubscriber : public QThread
{

public:

    /**
     * @brief Default Constructor
     *
     * @param topicName Name of Topic to subscribe
     */
    ActorsSubscriber(const std::string& topicName);

    /**
     * @brief Destructor
     *
     */
    virtual ~ActorsSubscriber();

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
     * @brief Method For ROS Callbak Function
     *
     * @param data Actors Container
     */
    void actorCallback(const actor_msgs::ActorVecConstPtr& data);

    /**
     * @brief Method to set Actors Data
     *
     * @param data Actors Container
     */
    void setActorsData(const actor_msgs::ActorVecConstPtr& data);

    /**
     * @brief Method to get Actors Data
     *
     * @param data Actors Container
     */
    void getActorsData(actor_msgs::ActorVec& data);

public:

    bool runThread; /**< Thread Run Flag  */

    std::string mTopicName; /**< Topic Name */

    QMutex mActorsDataMutex; /**< Actors Data Mutex */
    actor_msgs::ActorVec mActorData; /**< Actors Data Container */

    ros::NodeHandle n; /**< ROS Node */
    ros::Subscriber _sub; /**< ROS Subscriber */

};
};

#endif /*ACTORSSUBSCRIBER_H_*/

