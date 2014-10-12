#include "tflistener_helper.h"

TFListenerHelper::TFListenerHelper()
{
    tf_server = nh.advertiseService("/world_model/get_transform", &TFListenerHelper::tf_service_callback, this);
}

/*
  Implement this callback function for the tf_service server.
  This service takes the base_frame and target_frame as arguments, queries ros::tf for the transformation between these frames, and returns the result of this query. 

  req - data structure containing the transformation request. (explained in file world_model_srvs/srv/GetTransform.srv)
  res - data structure containing the result of the transformation query to ros::tf. (explained in file world_model_srvs/srv/GetTransform.srv)
*/


bool TFListenerHelper::tf_service_callback(world_model_srvs::GetTransformRequest &req, world_model_srvs::GetTransformResponse &res)
{
    tf::TransformListener listener;

    tf::StampedTransform stamped_transform;
    try{
        /*wait for transform to be published for 1.0sec*/
        listener.waitForTransform(req.target_frame, req.base_frame,
                                  ros::Time(0), ros::Duration(1.0));
        
	/*get the transform*/
        listener.lookupTransform(req.target_frame, req.base_frame,
                                 ros::Time(0), stamped_transform);
        // std::cout << stamped_transform.getOrigin().x() << ", " << stamped_transform.getOrigin().y() << ", " << stamped_transform.getOrigin().z() << std::endl;
        res.pose.position.x = stamped_transform.getOrigin().x();
        res.pose.position.y = stamped_transform.getOrigin().y();
        res.pose.position.z = stamped_transform.getOrigin().z();

        res.pose.orientation.w = stamped_transform.getRotation().getW();
        res.pose.orientation.x = stamped_transform.getRotation().getX();
        res.pose.orientation.y = stamped_transform.getRotation().getY();
        res.pose.orientation.z = stamped_transform.getRotation().getZ();

        res.success = true;
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();

        res.error_msg = ex.what();
        res.success = false;
    }

    return true;
}
