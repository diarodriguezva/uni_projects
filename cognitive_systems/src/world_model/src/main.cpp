#include <ros/ros.h>
#include <robot_control_srvs/GetPose.h>
#include <actor_msgs/ActorVec.h>
#include <cstdlib>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <math.h>

/*
    utility function for querying robot poses from the robot_control nodes and publishing them as tf's
    n - node handle for the world_model node
    service_name - name of the robot_control ROS service which provides the poses
    robot_name - name of the robot (gripperbot / cambot)
    base_frame - base frame for the transformation
    tf_frame - target frame for the transformation
*/
bool publish_robot_frame_tf(ros::NodeHandle &n, std::string service_name, std::string robot_name, std::string base_frame, std::string tf_frame)
{
    static tf::TransformBroadcaster br;
    ros::ServiceClient client = n.serviceClient<robot_control_srvs::GetPose>(service_name);
    robot_control_srvs::GetPose srv;
    srv.request.effector = tf_frame;
    if (client.call(srv)) //calling the service to get the robot pose
    {
        tf::Transform transform;
        transform.setOrigin( tf::Vector3(srv.response.x, srv.response.y, srv.response.z) );
        tf::Quaternion q;
        q.setRPY(0, 0, 0);
        transform.setRotation(q);
        std::stringstream ss_base;
        ss_base << robot_name << "_" << base_frame;
        std::stringstream ss_frame;
        ss_frame << robot_name << "_" << tf_frame;
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), ss_base.str(), ss_frame.str()));
    }
    else
    {
        ROS_ERROR("Failed to call service");
        return 1;
    }
}

/*
    callback function for fetching object poses from the object_detector node and publishing them as tf's
    objects - a vector of the objects detected
*/
void objectsCallback(const actor_msgs::ActorVec &objects)
{
    static tf::TransformBroadcaster br;
    for(size_t object_id = 0;object_id < objects.ActorVec.size();object_id++)
    {
        tf::Transform transform;
        transform.setOrigin( tf::Vector3(objects.ActorVec[object_id].targetPoseVec[0].position.x/1000.0,
                                         objects.ActorVec[object_id].targetPoseVec[0].position.y/1000.0,
                                         objects.ActorVec[object_id].targetPoseVec[0].position.z/1000.0) );
        tf::Quaternion q;
        q.setX(objects.ActorVec[object_id].targetPoseVec[0].orientation.x);
        q.setY(objects.ActorVec[object_id].targetPoseVec[0].orientation.y);
        q.setZ(objects.ActorVec[object_id].targetPoseVec[0].orientation.z);
        q.setW(objects.ActorVec[object_id].targetPoseVec[0].orientation.w);

        transform.setRotation(q);
        std::stringstream ss_object_name;
        ss_object_name << objects.ActorVec[object_id].targetProperty << "_" << objects.ActorVec[object_id].targetType << "_" << objects.ActorVec[object_id].targetId;
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "cambot_wrist", ss_object_name.str()));
    }
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "world_model");
    ros::NodeHandle n;

    tf::TransformListener listener;
    static tf::TransformBroadcaster br;

    ros::Subscriber sub = n.subscribe("/object_detector/objects_data", 1, objectsCallback);


    while(ros::ok())
    {
        /*
            tf's which need to be queried from the robot_control nodes. The robots are moving and hence the tf's change.
        */
        publish_robot_frame_tf(n, "/gripperbot_control/get_pose", "gripperbot", "base", "gripper");
        publish_robot_frame_tf(n, "/gripperbot_control/get_pose", "gripperbot", "base", "wrist");

        /*

            PUT YOUR CODE HERE!
            Only the transformations for the gripperbot have been implemented above.
            Do the same for the cambot. The cambot has 'camera' and 'wrist' frames

        */

        publish_robot_frame_tf(n, "/cambot_control/get_pose", "cambot", "base", "camera");
        publish_robot_frame_tf(n, "/cambot_control/get_pose", "cambot", "base", "wrist");


        /*
            Publishing transform between gripperbot_base and cambot_base
        */

        /*

            PUT YOUR CODE HERE
            Publish a transformation of the cambot_base w.r.t. gripperbot_base. (see lines 24-33 for a sample)
            The Z axes of the robots are aligned. The X and Y axes are inverted. (rotation around z axis of 180 degrees)
            The distance between the robots in X direction is 0.628m
        */

        tf::Transform transform;
        transform.setOrigin( tf::Vector3(0.628, 0, 0) );
        tf::Quaternion q;
        q.setRPY(0, 0, M_PI);
        transform.setRotation(q);

        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "gripperbot_base", "cambot_base"));

        ros::spinOnce();

        /*
            sample query to tf: pose of GREEN_BOX_0 w.r.t. gripperbot_base
            the query throws an error if the transformation hasn't been found, which needs to be catched.
        */

        tf::StampedTransform stamped_transform;
        try{
            /*wait for transform to be published for 1.0sec*/
            listener.waitForTransform("GREEN_BOX_0", "gripperbot_base",
                                      ros::Time(0), ros::Duration(1.0));
            /*get the transform*/
            listener.lookupTransform("GREEN_BOX_0", "gripperbot_base",
                                     ros::Time(0), stamped_transform);
            std::cout << stamped_transform.getOrigin().x() << ", " << stamped_transform.getOrigin().y() << ", " << stamped_transform.getOrigin().z() << std::endl;
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }

        ros::spinOnce();
    }

    return 0;
}
