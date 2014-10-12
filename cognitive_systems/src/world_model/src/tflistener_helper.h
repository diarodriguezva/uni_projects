#ifndef TFLISTENER_HELPER_H
#define TFLISTENER_HELPER_H
#include <ros/ros.h>
#include <cstdlib>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <world_model_srvs/GetTransform.h>

class TFListenerHelper
{
public:
    TFListenerHelper();
    tf::TransformListener listener;
    ros::ServiceServer tf_server;
    ros::NodeHandle nh;
    bool tf_service_callback(world_model_srvs::GetTransformRequest &req, world_model_srvs::GetTransformResponse &res);

};

#endif // TFLISTENER_HELPER_H
