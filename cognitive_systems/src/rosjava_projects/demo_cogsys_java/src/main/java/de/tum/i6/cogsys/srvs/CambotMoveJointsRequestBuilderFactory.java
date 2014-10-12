package de.tum.i6.cogsys.srvs;

public class CambotMoveJointsRequestBuilderFactory extends
		MoveJointsRequestBuilderFactory {

	@Override
	public String getServiceName() {
		return "cambot_control/move_joints";
	}

}
