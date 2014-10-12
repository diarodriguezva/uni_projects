/*
	Description:	Robot-specific parameters: NAO robot.
*/

// NAO robot-specific h-files for the joint msgs.
#include <JointState.h>
#include <JointAnglesWithSpeed.h>
#include <TactileTouch.h>
#include <Bumper.h>
#include <LegPosition.h>
#include <cmdLegState.h>

#define ROBOT_JOINTS		26			// robot-specific; NAO robot has 26 joints in all
#define HEAD_JOINTS         2
#define L_ARM_JOINTS		6
#define L_LEG_JOINTS        6
#define R_LEG_JOINTS		6
#define R_ARM_JOINTS		6
