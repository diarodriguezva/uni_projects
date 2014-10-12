#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <std_msgs/String.h>
//#include <dummy_robot_control/PrintGripperPose.h>
#include <dummy_robot_control/PrintPose.h>
#include <dummy_robot_control/MoveJoints.h>
#include <world/detect_objects.h>
#include <world/found_objects.h>
#include <world/inspect_objects.h>
#include <world/is_cam_moving_msg.h>
#include <world/check_goal_positions.h>
#include <ball_detection/find_boxes.h>
#include <ball_detection/find_balls.h>

// Measuremets
#define DIAMETER_BALL 70 //mm
#define NUMBER_BALLS 3
#define CAM_EFFECTOR_1 0.09
#define CAM_EFFECTOR_2 0.03
#define CAM_GRIPPER_1 0.44  // X respect to world
#define CAM_GRIPPER_2 0.35   // Y respect to world

// Parameters for the Workspace_inspection
#define N_STEPS_INSPECTION 4
#define INIT_POSITION_INSPECT -0.2

using namespace cv;
using namespace std;

// Topic, message and flag to check is the camera is moving
ros::Publisher cam_state_pub;
world::is_cam_moving_msg msg;
bool cam_moving = false;

// Name of the the transformations of each ball
String ss[3] = {"tf_green_start","tf_red_start","tf_yellow_start"};

String names[3] = {"green","red","yellow"};

// Variables that save the positions of the objects given by "inspect_workspace"
double x_found[3] = {0,0,0};
double y_found[3] = {0,0,0};
double z_found[3] = {0,0,0};
string name_found[3] = {"", "", ""};

deque<double> green_x_found_deque;
deque<double> green_y_found_deque;
deque<double> green_radius_found_deque;

deque<double> red_x_found_deque;
deque<double> red_y_found_deque;
deque<double> red_radius_found_deque;

deque<double> yellow_x_found_deque;
deque<double> yellow_y_found_deque;
deque<double> yellow_radius_found_deque;

bool getCambotPosition(double &, double &, double &, double &);
bool getObjectPositions(double*, double*, double*, string*);
bool moveCambot(double, double, double);
bool inspectHorizontally(double*, double*, double*, string*);

// Service to get the position of the end-effector of cambot
dummy_robot_control::MoveJoints srv;

void median(double &x, double &y, double &radius, string name){
    deque<double> x_aux;
    deque<double> y_aux;
    deque<double> radius_aux;

    if(name == "green"){

        green_x_found_deque.push_back(x);
        green_y_found_deque.push_back(y);
        green_radius_found_deque.push_back(radius);

        x_aux = green_x_found_deque;
        y_aux = green_y_found_deque;
        radius_aux = green_radius_found_deque;
    }

    if(name == "red"){
        red_x_found_deque.push_back(x);
        red_y_found_deque.push_back(y);
        red_radius_found_deque.push_back(radius);

        x_aux = red_x_found_deque;
        y_aux = red_y_found_deque;
        radius_aux = red_radius_found_deque;
    }

    if(name == "yellow"){
        yellow_x_found_deque.push_back(x);
        yellow_y_found_deque.push_back(y);
        yellow_radius_found_deque.push_back(radius);

        x_aux = yellow_x_found_deque;
        y_aux = yellow_y_found_deque;
        radius_aux = yellow_radius_found_deque;
    }

    sort(x_aux.begin(), x_aux.end());
    sort(y_aux.begin(), y_aux.end());
    sort(radius_aux.begin(), radius_aux.end());

    x = x_aux[(int)x_aux.size()/2];
    y = y_aux[(int)y_aux.size()/2];
    radius = radius_aux[(int)radius_aux.size()/2];
}

void printDeque(){
//    cout << "Elem_deque: " << x_found_deque.size() << endl;
//    for(int i=0; i < (x_found_deque.size()) ; i++){
//        cout << "x[" << i << "]: " << x_found_deque[i] << " ";
//        cout << "radius[" << i << "]: " << radius_found_deque[i] << " ";
//    }
//    cout << endl;
}

void clearDeques(){
    green_x_found_deque.clear();
    green_y_found_deque.clear();
    green_radius_found_deque.clear();

    red_x_found_deque.clear();
    red_y_found_deque.clear();
    red_radius_found_deque.clear();

    yellow_x_found_deque.clear();
    yellow_y_found_deque.clear();
    yellow_radius_found_deque.clear();
}

bool serviceCallbackInspect(world::inspect_objects::Request &req,
                            world::inspect_objects::Response &res)
{
    clearDeques();

    moveCambot(0,0,0);
//    moveCambot(INIT_POSITION_INSPECT,0,0.55);
    moveCambot(INIT_POSITION_INSPECT,-0.6,0.7);
    waitKey(3000);

    double x[3] = {0,0,0};
    double y[3] = {0,0,0};
    double z[3] = {0,0,0};
    string name[3] = {"", "", ""};

    bool found, aux;

    found = inspectHorizontally(x, y, z, name);
    //moveCambot(INIT_POSITION_INSPECT,-0.6,0.7);
    //aux = inspectHorizontally(x, y, z, name);

    //found = found || aux;

    for(int i=0; i<3; i++){
        median(x[i], y[i], z[i], name[i]);

        res.x[i] = x[i];
        res.y[i] = y[i];
        res.z[i] = z[i];
        res.name[i] = name[i];

        x_found[i] = x[i];
        y_found[i] = y[i];
        z_found[i] = z[i];
        name_found[i] = name[i];
    }
    moveCambot(0,-0.6,0.7);

    return found;
}

bool inspectHorizontally(double* x, double* y, double* z, string* name){

    double rate = 0.2;

    double x_aux[3] = {0,0,0};
    double y_aux[3] = {0,0,0};
    double z_aux[3] = {0,0,0};
    string name_aux[3] = {"", "", ""};

    bool found;

    for(int i=1; i < N_STEPS_INSPECTION + 1; i++){

        found = getObjectPositions(x_aux, y_aux, z_aux, name_aux);

        for(int j=0; j<3; j++){
            if((name_aux[j] == ""))
                break;
            else if(!(name_aux[j] == name[0] || name_aux[j] == name[1] || name_aux[j] == name[2])){
                for(int k=0; k<3; k++){
                    if(name[k] == ""){
                        name[k] = name_aux[j];
                        x[k] = x_aux[j];
                        y[k] = y_aux[j];
                        z[k] = z_aux[j];
                        break;
                    }
                }
            }
            else{
                for(int k=0; k<3; k++){
                    if(name[k] == name_aux[j]){

                        double diff_x = x[k] - x_aux[j];
                        double diff_y = y[k] - y_aux[j];

                        if(diff_x < DIAMETER_BALL && diff_y < DIAMETER_BALL){
                            x[k] = (x[k] + x_aux[j])/2;
                            y[k] = (y[k] + y_aux[j])/2;
                        }
                        else{
                            x[k] = x_aux[j];
                            y[k] = y_aux[j];
                            z[k] = z_aux[j];
                        }
                    }
                }
            }
        }
	
        moveCambot(INIT_POSITION_INSPECT+i*rate,-1000,-1000);
        waitKey(3000);
    }

    return found;
}

bool moveCambot(double q0, double q1, double q2){

    cam_moving = true;

    msg.cam_state = cam_moving;
    cam_state_pub.publish(msg);

    ros::NodeHandle nh;

    ros::ServiceClient cambotMoveJoints = nh.serviceClient<dummy_robot_control::MoveJoints>("/cambot_control/move_joints");

    if(q0 != -1000)
        srv.request.q0 = q0;
    if(q1 != -1000)
        srv.request.q1 = q1;
    if(q2 != -1000)
        srv.request.q2 = q2;

    if(!(cambotMoveJoints.call(srv))){
        ROS_ERROR("An error has ocurred trying to move the cambot");
        return false;
    }

    cam_moving = false;

    msg.cam_state = cam_moving;
    cam_state_pub.publish(msg);

    return true;
}

bool getCambotPosition(double &x_cam, double &y_cam, double &z_cam, double &yaw_cam){
    ros::NodeHandle nh;

    ros::ServiceClient clientCambotControl = nh.serviceClient<dummy_robot_control::PrintPose>("/cambot_control/print_pose");
    dummy_robot_control::PrintPose srv;

    srv.request.effector = "wrist";
    if(clientCambotControl.call(srv))
    {
        x_cam = srv.response.x;
        y_cam = srv.response.y;
        z_cam = srv.response.z;
        yaw_cam = atan2(y_cam, x_cam);
        //cout << yaw_cam << endl;
        return true;
    }
    else
    {
        return false;
    }
}

bool getObjectPositions(double* x, double* y, double* z, string* name){

    double x_cam, y_cam, z_cam, yaw_cam;
    if(!getCambotPosition(x_cam, y_cam, z_cam, yaw_cam)){
        return false;
    }

    int counter = 0, aux_elem = 0;

    tf::TransformListener listener;
    tf::StampedTransform transform;
    tf::StampedTransform listen_cam;
    static tf::TransformBroadcaster br;

    while(1){

        tf::Transform transform_cam_gripper;
        transform_cam_gripper.setOrigin(tf::Vector3(CAM_GRIPPER_1,-CAM_GRIPPER_2,0));
        transform_cam_gripper.setBasis(btMatrix3x3(0,-1,0,1,0,0,0,0,1));
        br.sendTransform(tf::StampedTransform(transform_cam_gripper,ros::Time::now(),"world","cam_base"));

        tf::Transform transform_cam;
        transform_cam.setOrigin(tf::Vector3(x_cam,y_cam,z_cam));
        transform_cam.setBasis(btMatrix3x3(sin(yaw_cam),0,cos(yaw_cam),-cos(yaw_cam),0,sin(yaw_cam),0,-1,0));
        br.sendTransform(tf::StampedTransform(transform_cam,ros::Time::now(),"cam_base","cam_effector"));

        // ****************************************************************** Verify Waitkey() !!!
        waitKey(3);

        try{
            for(int i=aux_elem; i<3; i++){
                listener.lookupTransform("world", ss[i],ros::Time(0), transform);
                listener.lookupTransform("cam_effector", ss[i],ros::Time(0), listen_cam);

                // If there is an object
                if (!(listen_cam.getOrigin().x() == CAM_EFFECTOR_2 && listen_cam.getOrigin().y() == 0 && listen_cam.getOrigin().z() == CAM_EFFECTOR_1)){
                    x[counter] = transform.getOrigin().x();
                    y[counter] = transform.getOrigin().y();
                    z[counter] = transform.getOrigin().z();
                    name[counter] = names[i];
                    counter++;
                }
                aux_elem++;

                // To get out of the While loop
                if(i==2)
                    return true;
            }
        }
        catch (tf::TransformException ex){
            //ROS_ERROR("%s",ex.what());
        }
    }

}

bool serviceCallbackFoundObjects(world::found_objects::Request &req,
                                 world::found_objects::Response &res)
{    
    for(int i=0; i<3; i++){
        res.x[i] = x_found[i];
        res.y[i] = y_found[i];
        res.z[i] = z_found[i];
        res.name[i] = name_found[i];
    }

    return true;
}

bool serviceCallbackDetectObjects(world::detect_objects::Request &req,
                                  world::detect_objects::Response &res)
{
    double x[3] = {0,0,0};
    double y[3] = {0,0,0};
    double z[3] = {0,0,0};
    string name[3] = {"", "", ""};

    bool success = getObjectPositions(x, y, z, name);

    for(int i=0; i<3; i++){
        res.x[i] = x[i];
        res.y[i] = y[i];
        res.z[i] = z[i];
        res.name[i] = name[i];
    }

    return success;
}

bool serviceCallbackCheckGoalPositions(world::check_goal_positions::Request &req,
                                       world::check_goal_positions::Response &res)
{
    ros::NodeHandle nh;

    ros::ServiceClient clientBoxes = nh.serviceClient<ball_detection::find_boxes>("/ball_detection/find_boxes");
    ball_detection::find_boxes srv_boxes;
    ros::ServiceClient clientBalls = nh.serviceClient<ball_detection::find_balls>("/ball_detection/find_balls");
    ball_detection::find_balls srv_balls;

    int x_min[3], x_max[3], y_min[3], y_max[3], x[3], y[3];
    string  color[3], name[3];

    if(clientBoxes.call(srv_boxes))
    {
        for(int k=0; k<3; k++){
            x_min[k] = srv_boxes.response.x_min[k];
            x_max[k] = srv_boxes.response.x_max[k];
            y_min[k] = srv_boxes.response.y_min[k];
            y_max[k] = srv_boxes.response.y_max[k];
            color[k] = srv_boxes.response.color[k];
        }
    }

    if(clientBalls.call(srv_balls))
    {
        for (int k=0; k<3; k++){
            x[k] = srv_balls.response.x[k];
            y[k] = srv_balls.response.y[k];
            name[k] = srv_balls.response.name[k];
        }
    }

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "world");
    ros::NodeHandle nh;

    // Topics
    cam_state_pub = nh.advertise<world::is_cam_moving_msg>("world/is_cam_moving",20);

    // Service for the list of objects
    std::stringstream ss0;
    std::stringstream ss1;
    std::stringstream ss2;
    std::stringstream ss3;
    std::stringstream ss4;

    ss0 << "/world/detect_objects";
    ss1 << "/world/found_objects";
    ss2 << "/world/inspect_workspace";
    ss3 << "/world/is_cam_moving";
    ss4 << "/world/check_goal_position";

    ros::ServiceServer service_list0 = nh.advertiseService(ss0.str(), serviceCallbackDetectObjects);
    ros::ServiceServer service_list1 = nh.advertiseService(ss1.str(), serviceCallbackFoundObjects);
    ros::ServiceServer service_list2 = nh.advertiseService(ss2.str(), serviceCallbackInspect);
    //ros::ServiceServer service_list3 = nh.advertiseService(ss3.str(), serviceCallbackIsCamMoving);
    ros::ServiceServer service_list4 = nh.advertiseService(ss4.str(), serviceCallbackCheckGoalPositions);

//    ros::spin();

    ros::Rate loop_rate(1);

    while(ros::ok())
    {
        msg.cam_state = cam_moving;
        cam_state_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
}
