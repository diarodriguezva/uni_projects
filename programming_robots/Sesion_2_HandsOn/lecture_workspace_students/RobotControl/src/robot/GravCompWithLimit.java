package robot;

import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;

public class GravCompWithLimit extends RoboticsAPIApplication {

	@Override
	public void run() {
	}

	/**
	 * Auto-generated method stub. Do not modify the contents of this method.
	 */
	public static void main(String[] args) {
		GravCompWithLimit app = new GravCompWithLimit();
		RobotController.initialize(app);

		RobotController.getInstance().gravCompImpedance();
	}
}
