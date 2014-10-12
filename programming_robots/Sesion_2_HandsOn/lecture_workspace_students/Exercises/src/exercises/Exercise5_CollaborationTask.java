package exercises;

import robot.RobotController;

import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;
import com.kuka.roboticsAPI.deviceModel.LBR;
import com.kuka.roboticsAPI.geometricModel.ObjectFrame;

public class Exercise5_CollaborationTask extends RoboticsAPIApplication {

	public static void main(String[] args) {
		// initialization
		Exercise5_CollaborationTask app = new Exercise5_CollaborationTask();
		RobotController.initialize(app);
		RobotController.createInfoGui();

		app.run();
	}

	private RobotController robotControl = null;
	private LBR robot = null;
	private ObjectFrame tool = null;

	@Override
	public void run() {
		robotControl = RobotController.getInstance();
		robot = robotControl.getRobot();
		tool = robotControl.getTool().getDefaultMotionFrame();

		System.out.println("Starting " + this.getClass().getSimpleName());

		while (true) {
		}
	}
}
