package de.tum.i6.cogsys.srvs;

public class GripperbotMoveToCSRequestBuilderFactory extends
		MoveToCSRequestBuilderFactory {

	@Override
	public String getServiceName() {
		return "gripperbot_control/move_to_cs";
	}

}
