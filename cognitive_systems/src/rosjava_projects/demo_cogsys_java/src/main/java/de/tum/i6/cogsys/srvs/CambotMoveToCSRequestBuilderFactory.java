package de.tum.i6.cogsys.srvs;

public class CambotMoveToCSRequestBuilderFactory extends
		MoveToCSRequestBuilderFactory {

	@Override
	public String getServiceName() {
		return "cambot_control/move_to_cs";
	}

}
