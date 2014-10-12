/** BEGIN LICENCE ************************************************************/
/* Copyright 2011-2012 TUM-fortiss                    */
/* All Rights Reserved.                                                      */
/* Permission to use, copy, modify OR distribute this software and its       */
/* documentation for educational, research and non-profit purposes, without  */
/* fee, and without a written agreement is hereby granted, provided that the */
/* above copyright notice and the following three paragraphs appear in all   */
/* copies.                                                                   */
/*                                                                           */
/* IN NO EVENT SHALL TUM-fortiss BE                                          */
/* LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR         */
/* CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE         */
/* USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE TECHNISCHE        */
/* UNIVERSITAET MUENCHEN HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH        */
/* DAMAGES.                                                                  */
/*                                                                           */
/* THE TUM-fortiss SPECIFICALLY DISCLAIMS ANY           */
/* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF      */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE       */
/* PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE TECHNISCHE             */
/* UNIVERSITAET MUENCHEN HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE,          */
/* SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.                         */
/*                                                                           */
/* Contact author: Suraj Nair                                                */
/* E-mail: nair@fortiss.org, nair@in.tum.de	                             */
/* If you have any questions regarding this agreement or the licensing of    */
/* this technology, please send them to the contact author above.            */
/*                                                                           */
/* Author(s):                                                                */
/* Suraj Nair nair@fortiss.org, nair@in.tum.de	                             */
/** END LICENCE **************************************************************/

#ifndef UTIL_H_
#define UTIL_H_

#include <actor_msgs/ActorVec.h>
#include <action_msgs/ActionVec.h>
#include <iostream>
#include <iomanip>
#include <comm_lib/CommonDefs.h>

namespace util
{
    /**
     * @brief Utility Class for accessing ROS message related data
     *
     */
    class Util
    {
    public:

/**
 * @brief Default Constructor
 *
 */
        Util();
        /**
         * @brief Destructor
         *
         */
        ~Util();

        /**
         * @brief Staticf function to get number of actors in a Actors Container
         *
         * @param actors
         */
        static int getNumberOfActors(const actor_msgs::ActorVec& actors);

        //Pose data is Vector(6) position and rotation
        //return true if found else false
        /**
         * @brief Static function to get Pose of a specific actor (type, property, id)
         *
         * @param actors Actors Container
         * @param targetType Target type
         * @param targetProperty Target property
         * @param targetId Target Id
         * @param poseData Pose Data (output)
         */
        static bool getActorPose(const actor_msgs::ActorVec& actors,
                                 const std::string& targetType,
                                 const std::string& targetProperty,
                                 const int& targetId,
                                 PoseVec& poseData);

        //returns pose of first actor which matches targetType
        /**
         * @brief Static function to get Pose of a specific actor (type)
         *
         * @param actors Actors Container
         * @param targetType Target type
         * @param poseData Pose Data (output)
         */
        static bool getActorPose(const actor_msgs::ActorVec& actors,
                                    const std::string& targetType,
                                    PoseVec& poseData);

        /**
         * @brief Static function to get Pose of a specific actor (type)
         *
         * @param actors Actors Container
         * @param targetType Target type
         * @param poseData Pose Data (output)
         */
        static bool getActorsOfType(const actor_msgs::ActorVec& actors,
                                    const std::string& targetType,
                                    actor_msgs::ActorVec& output);

        /**
         * @brief Static function to get all actors of a specific (type, property)
         *
         * @param actors Actors Container
         * @param targetType Target type
         * @param targetProperty Target property
         * @param output Actors Container (output)
         */
        static bool getActorsOfType(const actor_msgs::ActorVec& actors,
                                    const std::string& targetType,
                                    const std::string& targetProperty,
                                    actor_msgs::ActorVec& output);

        /**
         * @brief Static function to get all actors of a specific (type, property, id)
         *
         * @param actors Actors Container
         * @param targetType Target type
         * @param targetProperty Target property
         * @param targetId Target Id
         * @param output Actors Container (output)
         */
        static bool getActorsOfType(const actor_msgs::ActorVec& actors,
                                    const std::string& targetType,
                                    const std::string& targetProperty,
                                    const int& targetId,
                                    actor_msgs::ActorVec& output);

        /**
         * @brief Static function to check if a actor of a specific (type, property, id) is present
         *
         * @param actors Actors Container
         * @param targetType Target type
         * @param targetProperty Target property
         * @param targetId Target id
         */
        static bool isPresent(const actor_msgs::ActorVec& actors,
                              const std::string& targetType,
                              const std::string& targetProperty,
                              const int& targetId);

        /**
         * @brief Static function to check if a actor of a specific (type) is present
         *
         * @param actors Actors Container
         * @param targetType Target type
         */
        static bool isPresent(const actor_msgs::ActorVec& actors,
                              const std::string& semanticName);

//        //get unique actor by passing a concatinated string of type and id eg "MetaChassis" + "18901" = "MetalChassis18901"
//        static bool getActor(const actor_msgs::ActorVec& actors,
//                                    const std::string& targetType_Id,
//                                    actor_msgs::Actor& output);

        /**
         * @brief Static function to get an Actor of a specific (type) from an Actors Container
         *
         * @param actors Actors Container
         * @param targetType Target type
         * @param output Actor (output)
         */
        static bool getActor(const actor_msgs::ActorVec& actors,
                                    const std::string& semanticName,
                                    actor_msgs::Actor& output);

        /**
         * @brief Static function to copy data from one Actor to another
         *
         * @param src Source Actor
         * @param dst Destination Actor
         */
        static void copyActorData(const actor_msgs::Actor& src, actor_msgs::Actor& dst);

        /**
         * @brief Static function to copy data from one Actors Container to another Actors Container
         *
         * @param src Source Actors Container
         * @param dst Destination Actors Container
         */
        static void copyActorDataContainer(const actor_msgs::ActorVec& src, actor_msgs::ActorVec& dst);

        /**
         * @brief Static function to clear and Actors data Container
         *
         * @param data Actors Conatiner
         */
        static void clearActorsDataContainer(actor_msgs::ActorVec& data);

        /**
         * @brief Static function to add new Actors to actual data Container
         *
         * @param new_actors New Actors Conatiner
         * @param actors_data Actors Conatiner
         */
        static void addActors(actor_msgs::ActorVec& new_actors,actor_msgs::ActorVec& actors_data);

        /**
         * @brief Static function to clear and Actions data Container
         *
         * @param data Actions Conatiner
         */
        static void clearActionData(action_msgs::ActionVec& data);

    };
}
#endif /* UTIL_H_ */
