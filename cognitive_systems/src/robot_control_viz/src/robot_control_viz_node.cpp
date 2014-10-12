/** BEGIN LICENSE ************************************************************/
//    Copyright 2011-2012 Cognition Factory
//    All rights reserved.
//
//    Any use, distribution or replication without a written permission
//    is prohibited.
//
//    The name "Cognition Factory" must not be used to endorse or promote
//    products derived from the source code without prior written permission.
//
//    You agree to indemnify, hold harmless and defend Cognition Factory from
//    and against any loss, damage, claims or lawsuits, including attorney's
//    fees that arise or result from your use the software.
//
//    THIS SOFTWARE IS PROVIDED "AS IS" AND "WITH ALL FAULTS", WITHOUT ANY
//    TECHNICAL SUPPORT OR ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
//    BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//    FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. ALSO, THERE IS NO
//    WARRANTY OF NON-INFRINGEMENT, TITLE OR QUIET ENJOYMENT. IN NO EVENT
//    SHALL COGNITION FACTORY OR ITS SUPPLIERS BE LIABLE FOR ANY DIRECT,
//    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
//    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
//    IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//    POSSIBILITY OF SUCH DAMAGE.
/** END LICENSE **************************************************************/

#include "ros/ros.h"
#include <robot_control_srvs/MoveToCS.h>
#include <robot_control_srvs/MoveToOS.h>
#include <robot_control_srvs/MoveJoints.h>
#include <robot_control_srvs/GetPose.h>
#include <iostream>
#include <sstream>
#include <string>

#include <rl/hal/Coach.h>
#include <rl/math/Vector.h>
#include <rl/math/Unit.h>
#include <rl/math/Transform.h>
#include <rl/math/Rotation.h>
#include <rl/math/Cubic.h>
#include <rl/math/Quintic.h>

#define CUBIC
//#define QUINTIC

#define EPSILON 0.001

::rl::hal::Coach *robot;
::rl::math::Vector3 current;
::rl::math::Transform wrist, gripper, cam;

int robot_type;

enum Robot_Type
{
	GRASPBOT,
	CAMBOT
};

bool calculateInverseWristPosition(const ::rl::math::Transform& t, ::rl::math::Vector& JointAngles)
{

	::rl::math::Vector2 t1(0.00, 0.132);
	::rl::math::Vector2 t2(0.05427, 0.0415);
	::rl::math::Real d1 = 0.19;
	::rl::math::Real d2 = 0.14;

	const ::rl::math::Real& x = t.translation().x();
	const ::rl::math::Real& y = t.translation().y();
	const ::rl::math::Real& z = t.translation().z();

	::rl::math::Real q0, q1, q2;

	q0 = atan2(y, x);

	::rl::math::Vector2 rz(::std::sqrt(::std::pow(x, 2) + ::std::pow(y, 2)), z);
	rz = rz - t1 - t2;

	if (rz(1) < 0.0)
		return false;

	::rl::math::Real rz_norm = rz.norm();
	if (rz_norm > d1 + d2 || rz_norm < std::abs(d1 - d2))
	{
		std::cerr << "This position is not reachable (too far away)" << std::endl;
		// Fail fast - this position is obviously not reachable
		return false;
	}

	::rl::math::Real b1 = acos(rz(0) / rz_norm);
	::rl::math::Real c1 = acos((::std::pow(d1, 2) + ::std::pow(rz_norm, 2) - ::std::pow(d2, 2)) / (2 * d1 * rz_norm));
	q1 = M_PI_2 - (b1 + c1);

	::rl::math::Real tmp = cos(b1 + c1) * d1;
	q2 = M_PI_2 - (asin((rz(0) - tmp) / d2));

	::rl::math::Real tmp2 = sin(b1 + c1) * d1;
	::rl::math::Real tmp3 = sin(q2) * d2;

	if (::std::abs((tmp2 - tmp3) - rz(1)) > ::std::abs((tmp2 + tmp3) - rz(1)))
		q2 *= -1;


		::rl::math::Vector2 rz_check = ::rl::math::Vector2(d1 * sin(q1),      d1 * cos(q1))
			+ ::rl::math::Vector2(d2 * cos(q2), -1 * d2 * sin(q2));


	// Check if position is reachable
	if (::std::abs((rz_check - rz).norm()) > EPSILON)
	{
		std::cerr << "Position not reachable: " << rz_check << " vs. " << rz << std::endl;
		return false;
	}

	::rl::math::Vector q(3);
	q << q0, q1, q2;

	JointAngles = q;
	return true;	


	// if (isValid(q))
	// {
	// 	JointAngles = q;
	// 	return true;
	// } else{
	// 	std::cerr << "Position is not valid" << std::endl;
	// 	return false;
	// }

}

bool moveTraj(::rl::math::Vector& goal)
{

	::rl::math::Vector q0 = current;
	::rl::math::Vector q1 = goal;

	if(q0(0)==q1(0) && q0(1)==q1(1) && q0(2)==q1(2) )
	{
		std::cout << "Current Position = Set position" << std::endl;
		return true;
	}

#ifdef CUBIC
	std::vector< rl::math::Cubic< rl::math::Real > > interpolator(robot->getDof());
#endif // CUBIC
#ifdef QUINTIC
	std::vector< rl::math::Quintic< rl::math::Real > > interpolator(robot->getDof());
#endif // QUINTIC

	rl::math::Real te = robot->getUpdateRate() * 300.0f;
	rl::math::Vector q(robot->getDof());

	for (std::size_t i = 0; i < interpolator.size(); ++i)
	{
		interpolator[i].te = te;
		interpolator[i].v0 = 0;
		interpolator[i].ve = 0;
#ifdef QUINTIC
		interpolator[i].a0 = 0;
		interpolator[i].ae = 0;
#endif // QUINTIC
	}

	for (std::size_t i = 0; i < interpolator.size(); ++i)
	{
		interpolator[i].x0 = q0(i);
		interpolator[i].xe = q1(i);
		interpolator[i].interpolate();
	}

	for (std::size_t i = 0; i <= std::ceil(te / robot->getUpdateRate()); ++i)
	{
		for (std::size_t j = 0; j < robot->getDof(); ++j)
		{
			q(j) = interpolator[j].x(i * robot->getUpdateRate());
		}

		robot->setJointPosition(q);
		robot->step();
	}

	current = goal;
	return true;
}

bool toCartesian(const ::rl::math::Vector3& intendedCartesianPosition, const ::std::string& effector, bool& serviceResponse){
	::rl::math::Transform temp;
	temp.setIdentity();
	temp = ::rl::math::AngleAxis(atan2(intendedCartesianPosition[1], intendedCartesianPosition[0]), ::rl::math::Vector3::UnitZ());
	temp.translation().x() = intendedCartesianPosition[0];
	temp.translation().y() = intendedCartesianPosition[1];
	temp.translation().z() = intendedCartesianPosition[2];

	// ::std::cout << "Temp: " << ::std::endl << temp.matrix() << ::std::endl;


	gripper.setIdentity();
    gripper.translation().x() = 0.15f;
	gripper.translation().y() = 0.0f;
	gripper.translation().z() = 0.0f;

	// ::std::cout << "Gripper: " << ::std::endl << gripper.matrix() << ::std::endl;

	// ::std::cout << "Gripper inverse: " << ::std::endl << gripper.inverse().matrix() << ::std::endl;

	// ::std::cout << "Angle: " << ::std::endl << atan2(intendedCartesianPosition[1], intendedCartesianPosition[0]) * ::rl::math::RAD2DEG << ::std::endl;

	cam.setIdentity();
    cam.translation().x() = 0.055f;
	cam.translation().y() = -0.027f;
	cam.translation().z() = -0.035f;

	// ::std::cout << "Cam: " << ::std::endl << cam.matrix() << ::std::endl;

	// ::std::cout << "Cam inverse: " << ::std::endl << cam.inverse().matrix() << ::std::endl;

	// ::std::cout << "Angle: " << ::std::endl << atan2(intendedCartesianPosition[1], intendedCartesianPosition[0]) * ::rl::math::RAD2DEG << ::std::endl;

	::rl::math::Transform intendedCartesianWrist;
	intendedCartesianWrist.setIdentity();
	if (effector == "gripper"){
		if(robot_type == GRASPBOT){
			// ::std::cout << "gripper" << ::std::endl;
			intendedCartesianWrist = temp * gripper.inverse();
		}
		else
		{
			::std::cout << "Not the correct effector" << ::std::endl;
			serviceResponse = false;
			return true;
		}
	}

	if (effector == "camera"){
		if(robot_type == CAMBOT){
			// ::std::cout << "camera" << ::std::endl;
			intendedCartesianWrist = temp * cam.inverse();
		}
		else
		{
			::std::cout << "Not the correct effector" << ::std::endl;
			serviceResponse = false;
			return true;
		}
	}


	if (effector == "wrist"){
		intendedCartesianWrist = temp;
	}

	// ::std::cout << "intendedCartesianWrist: " << ::std::endl << intendedCartesianWrist.matrix() << ::std::endl;

	::std::cout << "Intended Position: " << "\t" << intendedCartesianWrist.translation().x() << "\t" << intendedCartesianWrist.translation().y() << "\t" << intendedCartesianWrist.translation().z() << ::std::endl;
	::rl::math::Vector q0;
	if(calculateInverseWristPosition(intendedCartesianWrist,q0)){
		moveTraj(q0);
		wrist = intendedCartesianWrist;
		serviceResponse = true;
	} else {
		serviceResponse = false;
	}
	return true;
}

bool moveCartesian(robot_control_srvs::MoveToCS::Request &req, robot_control_srvs::MoveToOS::Response &res)
{
	// if ((req.effector == "gripper" && (req.z < 0.205 || req.x > 0.50)) || (req.effector == "wrist" && (req.z < 0.205 || req.x > 0.32))) {
	// 	res.success = false;
	// 	::std::cout << "Will not move " << req.effector << " to: x=" << req.x << " y=" << req.y << " z=" << req.z << " because of the table!" << ::std::endl;
	// 	return true;
	// }

	::rl::math::Vector intended(3);
	intended << req.x, req.y, req.z;
	bool success;
	bool functionResult = toCartesian(intended, req.effector, success);
	res.success = success;
	return functionResult;


}


bool moveJoint(robot_control_srvs::MoveJoints::Request &req, robot_control_srvs::MoveJoints::Response &res)
{
	// if (req.q1 > 0.61 || req.q2 > 0.71) {
	// 	res.success = false;
	// 	::std::cout << "Will not set joints to: q0=" << req.q0 << " q1=" << req.q1 << " q2=" << req.q2 << " because of the table!" << ::std::endl;
	// 	return true;
	// }

	::rl::math::Vector q0(3);
	q0 << req.q0, req.q1, req.q2;
	moveTraj(q0);
	res.success = true;
	return true;
}

bool getPose(robot_control_srvs::GetPose::Request &req, robot_control_srvs::GetPose::Response &res)
{
	if (req.effector == "gripper" && robot_type == GRASPBOT){
		::rl::math::Transform temp = wrist * gripper;

		res.x = temp.translation().x();
		res.y = temp.translation().y();
		res.z = temp.translation().z();
		res.success = true;
	}
	else if (req.effector == "camera" && robot_type == CAMBOT)
	{
		::rl::math::Transform temp = wrist * cam;

		res.x = temp.translation().x();
		res.y = temp.translation().y();
		res.z = temp.translation().z();
		res.success = true;
	}
	else if (req.effector == "wrist")
	{
		res.x = wrist.translation().x();
		res.y = wrist.translation().y();
		res.z = wrist.translation().z();
		res.success = true;
	}
	else
	{
		::std::cout << "Not the correct effector" << ::std::endl;
		res.success = false;
	}

	return true;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		::std::cerr << "Usage: " << argv[0] << " <robot_number>" << " <namespace>" << ::std::endl;
		return 1;
	}

	::rl::hal::Coach grapbot(3, 0.004f, 1);
	::rl::hal::Coach cambot(3, 0.004f, 0);

	if (atoi( argv[1] ) == 0)
	{	
		robot = &grapbot;
		current << 0.2f, 0.0, 0.f;
		robot_type = GRASPBOT;

	}
	else if (atoi( argv[1] ) == 1)
	{
		robot = &cambot; 
		current << 0.2f, -0.0, 0.f;
		robot_type = CAMBOT;
	}
	else
	{
		::std::cerr << "robot_number can only be 0 or 1" << ::std::endl;
	}

	robot->open();
	robot->start();
	robot->setJointPosition(current);
	robot->step();

	bool x;
	rl::math::Vector q = (rl::math::Vector(3) << 0, 0, 0.3).finished();
	toCartesian(q, "wrist", x);

	std::stringstream ss1;
	std::stringstream ss2;
	std::stringstream ss3;
	std::stringstream ss4;
	ss1 << "/" << argv[2] << "/move_to_cs";
	ss3 << "/" << argv[2] << "/move_joints";
	ss4 << "/" << argv[2] << "/get_pose";


	ROS_INFO("Advertising ROS services...");
	ros::init(argc, argv, argv[2]);
	ros::NodeHandle n;
	ros::ServiceServer serviceMoveCartesian = n.advertiseService(ss1.str(), &moveCartesian);
	ros::ServiceServer serviceMoveJoint = n.advertiseService(ss3.str(), &moveJoint);
	ros::ServiceServer serviceGetPose = n.advertiseService(ss4.str(), &getPose);

	ros::spin();

	robot->stop();
	robot->close();
}
