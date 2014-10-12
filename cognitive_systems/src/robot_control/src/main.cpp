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
#include <cf/r0/edu/R0.hpp>

using namespace ::cf::r0::edu;

R0 robot;

bool moveToCS(robot_control_srvs::MoveToCS::Request  &req,
         robot_control_srvs::MoveToCS::Response &res)
{
//    if ((req.effector == "gripper" && (req.z < 0.18 || req.x > 0.50)) ||
//        (req.effector == "wrist" && (req.z < 0.18 || req.x > 0.32))) {
//      res.success = false;
//      ::std::cout << "Will not move " << req.effector << " to: x=" << req.x << " y=" << req.y << " z=" << req.z << " because of the table!" << ::std::endl;
//      return true;
//    }
    Point p(req.x, req.y, req.z);
    Point p2;
    if (robot.moveToPosition(p, req.effector, ConfigurationSpace)) {
      res.success = true;
    } else {
      res.success = false;
    }
    robot.getEffectorPosition(req.effector, p2);
    ::std::cout << "Current effector (" << req.effector << ") position: x=" << p2.x << " y=" << p2.y << " z=" << p2.z << ::std::endl;
    return true;
}


bool moveToOS(robot_control_srvs::MoveToOS::Request &req,
         robot_control_srvs::MoveToOS::Response &res)
{
//    if ((req.effector == "gripper" && (req.z < 0.205 || req.x > 0.50)) ||
//        (req.effector == "wrist" && (req.z < 0.205 || req.x > 0.32))) {
//      res.success = false;
//      ::std::cout << "Will not move " << req.effector << " to: x=" << req.x << " y=" << req.y << " z=" << req.z << " because of the table!" << ::std::endl;
//      return true;
//    }
    Point p(req.x, req.y, req.z);
    Point p2;
    if (robot.moveToPosition(p, req.effector, OperationalSpace)) {
      res.success = true;
    } else {
      res.success = false;
    }
    robot.getEffectorPosition(req.effector, p2);
    ::std::cout << "Current effector (" << req.effector << ") position: x=" << p2.x << " y=" << p2.y << " z=" << p2.z << ::std::endl;
    return true;
}


bool moveJoints(robot_control_srvs::MoveJoints::Request &req,
         robot_control_srvs::MoveJoints::Response &res)
{
//    if (req.q1 > 0.61 || req.q2 > 0.71) {
//      res.success = false;
//      ::std::cout << "Will not set joints to: q0=" << req.q0 << " q1=" << req.q1 << " q2=" << req.q2 << " because of the table!" << ::std::endl;
//      return true;
//    }
    Point p2;
    if (robot.moveJoints(req.q0, req.q1, req.q2)) {
      res.success = true;
    } else {
      res.success = false;
    }
    robot.getEffectorPosition("wrist", p2);
    ::std::cout << "Current effector (wrist) position: x=" << p2.x << " y=" << p2.y << " z=" << p2.z << ::std::endl;
    return true;
}

bool getPose(robot_control_srvs::GetPose::Request &req,
         robot_control_srvs::GetPose::Response &res)
{
    Point p2;
    robot.getEffectorPosition(req.effector, p2);
    ::std::cout << "Current effector << " << req.effector << " position: x=" << p2.x << " y=" << p2.y << " z=" << p2.z << ::std::endl;

    res.x = p2.x;
    res.y = p2.y;
    res.z = p2.z;
	res.success = true;

    return true;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        ::std::cerr << "Usage: " << argv[0] << " <host>" << " <namespace>" << ::std::endl;
        return 1;
    }

    std::stringstream ss1;
    std::stringstream ss2;
    std::stringstream ss3;
    std::stringstream ss4;
    ss1 << "/" << argv[2] << "/move_to_cs";
    ss2 << "/" << argv[2] << "/move_to_os";
    ss3 << "/" << argv[2] << "/move_joints";
    ss4 << "/" << argv[2] << "/get_pose";

    EffectorMap effectors;
    effectors["wrist"] = Point(0.0f, 0.0f, 0.0f);
    effectors["gripper"] = Point(0.15f, 0.0f, 0.0f);
    effectors["camera"] = Point(0.055f, -0.027f, -0.035f);

    ROS_INFO("Connecting to robot...");
    robot.connect(argv[1], 7777);
    robot.setEffectors(effectors);
    ROS_INFO("  DONE");

    ROS_INFO("Advertising ROS services...");
    ros::init(argc, argv, argv[2]);
    ros::NodeHandle n;
    ros::ServiceServer service1 = n.advertiseService(ss1.str(), &moveToCS);
    // ros::ServiceServer service2 = n.advertiseService(ss2.str(), &moveToOS);
    ros::ServiceServer service3 = n.advertiseService(ss3.str(), &moveJoints);
    ros::ServiceServer service4 = n.advertiseService(ss4.str(), &getPose);

    ROS_INFO("  DONE");

    ros::spin();

    robot.disconnect();

    return 0;
}

