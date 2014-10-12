package de.tum.i6.cogsys.srvs;

public class GripperbotMoveJointsRequestBuilderFactory extends
		MoveJointsRequestBuilderFactory {

	@Override
	public String getServiceName() {
		return "gripperbot_control/move_joints";
	}

}
