/*
* 
* started by Suraj Nair
*/
#include <QApplication>
#include <stdexcept>
#include <exception>
#include <signal.h>
#include "main.h"
#include <comm_lib/ActorsSubscriber.h>
#include <comm_lib/util/Util.h>
#include <robot_control_srvs/MoveToOS.h>
#include <gripper_control_srvs/OpenGripper.h>
#include <gripper_control_srvs/CloseGripper.h>
#include <opencv2/opencv.hpp>
#include <speech_recognition_srvs/TurnOff.h>
#include <speech_recognition_srvs/TurnOn.h>
#include <speech_recognition_msgs/RecognizedSpeech.h>

using namespace std;

ros::ServiceClient gripperbot_client;
robot_control_srvs::MoveToOS gripperbot_srv;

ros::ServiceClient opengripper_client;
gripper_control_srvs::OpenGripper opengripper_srv;

ros::ServiceClient closegripper_client;
gripper_control_srvs::CloseGripper closegripper_srv;

comminterface::ActorsSubscriber* mSub;

ros::Subscriber sub_speech;

ros::ServiceClient mic_on_client;
speech_recognition_srvs::TurnOn mic_on_srv;

ros::ServiceClient mic_off_client;
speech_recognition_srvs::TurnOff mic_off_srv;

void  opengripper()
{
	std::cout << "Opening Gripper" << std::endl;
	if (opengripper_client.call(opengripper_srv))
	{
		if(opengripper_srv.response.success)
	    		std::cout << "OpenGripper successfull " <<std::endl;
		else
	    		std::cout << "OpenGripper failed" << std::endl;
	}
	else
	{
		ROS_ERROR("Failed to call service /gripper_control/open_gripper");
		throw;
	}
}

void closegripper()
{
	std::cout << "Closing Gripper" << std::endl;
	if (closegripper_client.call(closegripper_srv))
	{
		if(closegripper_srv.response.success)
	    		std::cout << "CloseGripper successfull " <<std::endl;
		else
	    		std::cout << "CloseGripper failed" << std::endl;
	}
	else
	{
		ROS_ERROR("Failed to call service /gripper_control/close_gripper");
		throw;
	}
}

void moverobot(float x, float y, float z)
{
	gripperbot_srv.request.x=x;
	gripperbot_srv.request.y=y;
	gripperbot_srv.request.z=z;
	gripperbot_srv.request.effector="gripper";

	if (gripperbot_client.call(gripperbot_srv))
	{
		if(gripperbot_srv.response.success)
	    		std::cout << "Approach successfull " <<std::endl;
		else
	    		std::cout << "Approach failed to " << x << " " << y << " " << z << std::endl;
	}
	else
	{
		ROS_ERROR("Failed to call service /robot_control/move_to_os");
		throw;
	}
}

void home()
{
    static float home_x=0.30;
	static float home_y=0.00;
	static float home_z=0.34;

	gripperbot_srv.request.x=home_x;
	gripperbot_srv.request.y=home_y;
	gripperbot_srv.request.z=home_z;

	std::cout << "Moving Robot to Home" << std::endl;
	moverobot(home_x,home_y,home_z);

}

void grasp(std::string type, std::string prop)
{

	actor_msgs::ActorVec objects;
	mSub->getActorsData(objects);
    //std::string type="BOX";
    //std::string prop="YELLOW";
	int id=0;

	PoseVec pose;
	if(util::Util::getActorPose(objects, type, prop, id, pose))
	{
        std::cout << prop << " " << type << " FOUND" << std::endl;
		std::cout << "Preparing to GRASP" << std::endl;

		float x,y,z;
		float bottom,top;
        x=(float)((650.0-pose[0](0))/1000.0);
        y=(float)((-1*pose[0](1))/1000.0);
		bottom=(float)(pose[0](2)/1000.0);
		top=(float)(bottom+0.05f);
		
		opengripper();


		std::cout << "Approaching object top" << std::endl;
		z=top;
		moverobot(x,y,z);

		std::cout << "Approaching object" << std::endl;
		z=bottom;
		moverobot(x,y,z);


		closegripper();

		std::cout << "Approaching top" << std::endl;
		z=top;
		moverobot(x,y,z);

        x = 0;
        y = -0.3;
        z = 0.3;
        moverobot(x,y,z);


		opengripper();

        home();

					
	}
	else
	{
		std::cout << "NO " << prop  << " " << type << "found to grasp" << std::endl;
	}
}

void turn_mic_off()
{
    mic_off_client.call(mic_off_srv);
}

void analyzeSpeech(const speech_recognition_msgs::RecognizedSpeechConstPtr &speech)
{
    std::string s = speech->speech;

    if (s.find("YELLOW") != string::npos)
    {
        turn_mic_off();
        grasp("BOX", "YELLOW");
    }
}


void turn_mic_on()
{
    mic_on_client.call(mic_on_srv);
}

int main(int argc, char** argv)
{
    try
    {
        ros::init(argc, argv, "demo_cogsys_cpp");

        cv::Mat demoImg(480,640, CV_8UC3);
        cv::namedWindow("demo", 1);

	demoImg=cv::Scalar(0,0,0);

	cv::putText(demoImg, "Press ESC to quit app", cv::Point(30,30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,255,0), 1, CV_AA);
    cv::putText(demoImg, "Press g to grasp GREEN object", cv::Point(30,70), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,255,0), 1, CV_AA);
	cv::putText(demoImg, "Please implement your own activation login for grasping", cv::Point(30,100), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,255,0), 1, 	CV_AA);
	cv::putText(demoImg, "using natural language (pressing 'g' is only for testing)", cv::Point(30,130), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,255,0), 1, CV_AA);
    cv::putText(demoImg, "Press m to activate microphone", cv::Point(30,160), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,255,0), 1, CV_AA);

        mSub = new comminterface::ActorsSubscriber("/object_detector/objects_data");
        mSub->start();

        int k;

	ros::NodeHandle n;

        gripperbot_client = n.serviceClient<robot_control_srvs::MoveToOS>("/gripperbot_control/move_to_cs");
        opengripper_client = n.serviceClient<gripper_control_srvs::OpenGripper>("/gripper_control/open_gripper");
        closegripper_client = n.serviceClient<gripper_control_srvs::CloseGripper>("/gripper_control/close_gripper");

        sub_speech = n.subscribe("/re_speech_recognition/output", 1, analyzeSpeech);
        mic_on_client = n.serviceClient<speech_recognition_srvs::TurnOn>("/re_speech_recognition/turn_on");
        mic_off_client = n.serviceClient<speech_recognition_srvs::TurnOff>("/re_speech_recognition/turn_off");

	home();

    bool graspObject = false;
        while(true)
        {

        if(graspObject)
		{
            grasp("BOX", "GREEN");
			graspObject=false;
        }

		imshow("demo",  demoImg);

		k = cv::waitKey(100);

		if((int)(k & 0xFF) == 27)
			break;

        if((int)(k & 0xFF) == 'g')
            graspObject=true;

        if((int)(k & 0xFF) == 'm')
            turn_mic_on();
        }

        demoImg.release();

        mSub->stopThread();

        cv::destroyWindow("demoImg");

	gripperbot_client.shutdown();
	opengripper_client.shutdown();
	closegripper_client.shutdown();
    mic_on_client.shutdown();
    mic_off_client.shutdown();
    delete mSub;

        return 1;

    }
    catch (std::exception& e)
    {

        std::cout << e.what() << endl;
    }

    return 0;
};



