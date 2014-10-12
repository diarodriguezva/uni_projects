package exercises;

import robot.RobotController;

import com.kuka.common.ThreadUtil;
import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;
import com.kuka.roboticsAPI.deviceModel.JointPosition;
import com.kuka.roboticsAPI.deviceModel.LBR;
import com.kuka.roboticsAPI.motionModel.BasicMotions;

public class Exercise3d_SingularPositions extends RoboticsAPIApplication {

	public static void main(String[] args) {
		// initialization
		Exercise3d_SingularPositions app = new Exercise3d_SingularPositions();
		RobotController.initialize(app);
		RobotController.createInfoGui();

		app.run();
	}

	RobotController robotControl;
	LBR robot;

	@Override
	public void run() {
		robotControl = RobotController.getInstance();
		robot = robotControl.getRobot();

		System.out.println("Starting " + this.getClass().getSimpleName());

		// create joint position target
		JointPosition target;

		// move to A4 singularity
		System.out.println("Moving to A4 singularity");
		target = new JointPosition(0, Math.toRadians(30), 0, Math.toRadians(-30), 0, Math.toRadians(90), 0);
		robot.move(BasicMotions.ptp(target).setJointVelocityRel(0.5));
		target.set(3, 0);
		robot.move(BasicMotions.ptp(target).setJointVelocityRel(0.1));
		ThreadUtil.milliSleep(2000);

		// move to A4/A6 singularity
		target = new JointPosition(0, 0, 0, Math.toRadians(-90), 0, Math.toRadians(30), 0);
		robot.move(BasicMotions.ptp(target).setJointVelocityRel(0.5));
		System.out.println("Moving to A4/A6 singularity");
		target = robot.getCurrentJointPosition();
		target.set(3, Math.toRadians(-90));
		target.set(5, Math.toRadians(0));
		robot.move(BasicMotions.ptp(target).setJointVelocityRel(0.1));
		ThreadUtil.milliSleep(2000);

		// move to A2/A3 singularity
		System.out.println("Moving to A2/A3 singularity");
		target = new JointPosition(Math.toRadians(-90), 0, Math.toRadians(60), Math.toRadians(-90), 0,
				Math.toRadians(90), 0);
		robot.move(BasicMotions.ptp(target).setJointVelocityRel(0.5));
		target.set(2, Math.toRadians(90));
		robot.move(BasicMotions.ptp(target).setJointVelocityRel(0.1));
		ThreadUtil.milliSleep(2000);

		// move to A5/A6 singularity
		System.out.println("Moving to A5/A6 singularity");
		target = new JointPosition(0, Math.toRadians(-45), 0, Math.toRadians(-90), Math.toRadians(60), 0, 0);
		robot.move(BasicMotions.ptp(target).setJointVelocityRel(0.5));
		target.set(4, Math.toRadians(90));
		robot.move(BasicMotions.ptp(target).setJointVelocityRel(0.1));
		ThreadUtil.milliSleep(2000);

		robotControl.goFront();
	}
}
