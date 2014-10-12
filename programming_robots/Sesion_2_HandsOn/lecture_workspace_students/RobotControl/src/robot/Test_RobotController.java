package robot;

import static com.kuka.roboticsAPI.motionModel.BasicMotions.ptpHome;

import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;

public class Test_RobotController extends RoboticsAPIApplication {

	@Override
	public void run() {
	}

	public static void main(String[] args) {
		Test_RobotController app = new Test_RobotController();
		RobotController.initialize(app);

		System.out.println("starting movement");
		RobotController.getInstance().getRobot().move(ptpHome());
		System.out.println("finished movement!");
	}
}
