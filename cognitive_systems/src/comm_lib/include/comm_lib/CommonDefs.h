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


#ifndef COMMONDEFS_H
#define COMMONDEFS_H

/********************************* Includes **********************************/
#include <iostream>
#include <vector>
#include <QSettings>
#include <QFileInfo>
#include <QTime>
#include <QThread>
#include <QMutex>
#include <Eigen/Eigen>
#include <vector>
#include <Eigen/StdVector>


/**
 * @brief Container for TargetPose
 *
 */
typedef Eigen::VectorXd TargetPose;
/**
 * @brief Container For Target Pose Vector
 *
 */
typedef std::vector<Eigen::VectorXd, Eigen::aligned_allocator<Eigen::VectorXd> > PoseVec;
/**
 * @brief Container for Point Sets
 *
 */
typedef std::vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d> > PointSets;
#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <QUuid>
/******************************* Defs and macros *****************************/
#include "util/Util.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef MIN
#define MIN(x,y) ( ( x < y )? x : y )
#endif
#ifndef MAX
#define MAX(x,y) ( ( x > y )? x : y )
#endif
#ifndef ABS
#define ABS(x) ( ( x < 0 )? -x : x )
#endif

/********************************** Structures *******************************/

#endif
