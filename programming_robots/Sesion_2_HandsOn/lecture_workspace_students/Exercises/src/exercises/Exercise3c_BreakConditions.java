package exercises;

import robot.RobotController;

import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;
import com.kuka.roboticsAPI.conditionModel.ForceCondition;
import com.kuka.roboticsAPI.deviceModel.LBR;
import com.kuka.roboticsAPI.geometricModel.CartDOF;
import com.kuka.roboticsAPI.geometricModel.Frame;
import com.kuka.roboticsAPI.geometricModel.Tool;
import com.kuka.roboticsAPI.geometricModel.math.CoordinateAxis;
import com.kuka.roboticsAPI.geometricModel.math.Transformation;
import com.kuka.roboticsAPI.motionModel.BasicMotions;
import com.kuka.roboticsAPI.motionModel.controlModeModel.CartesianImpedanceControlMode;

public class Exercise3c_BreakConditions extends RoboticsAPIApplication {

	public static void main(String[] args) {
		// initialization
		Exercise3c_BreakConditions app = new Exercise3c_BreakConditions();
		RobotController.initialize(app);
		RobotController.createInfoGui();

		app.run();
	}

	RobotController robotControl;
	LBR robot;
	Tool tool;

	@Override
	public void run() {
		robotControl = RobotController.getInstance();
		robot = robotControl.getRobot();
		tool = RobotController.getInstance().getTool();

		System.out.println("Starting " + this.getClass().getSimpleName());

		// load joint positions and create frames out of these. The robot will use redundancy information
		// from its current [at runtime when using a frame] configuration
		Frame firstFrame = new Frame(Transformation.ofDeg(400, 300, 350, 180, 0, -180));
		Frame secondFrame = new Frame(Transformation.ofDeg(400, -300, 350, 180, 0, -180));

		// move to start position
		robotControl.goFront();
		tool.move(BasicMotions.ptp(firstFrame).setJointVelocityRel(0.4));

		// create and configure CartesianImpedanceControlMode
		CartesianImpedanceControlMode cartImpMode = new CartesianImpedanceControlMode();

		// cartImpMode.parametrize(CartDOF.ALL).setStiffness(70);
		// cartImpMode.parametrize(CartDOF.ALL).setDamping(0.7);

		cartImpMode.parametrize(CartDOF.X).setStiffness(2500);
		cartImpMode.parametrize(CartDOF.X).setDamping(0.9);

		cartImpMode.parametrize(CartDOF.Y).setStiffness(2500);
		cartImpMode.parametrize(CartDOF.Y).setDamping(0.9);

		cartImpMode.parametrize(CartDOF.Z).setStiffness(2500);
		cartImpMode.parametrize(CartDOF.Z).setDamping(0.9);

		// cartImpMode.setNullSpaceDamping(0.3);
		// cartImpMode.setNullSpaceStiffness(0);

		// break condition which stops at 10% of a joints maximum torque
//		ICondition cond = RobotController.createJointTorqueCondition(0.1);

		// create a break condition for the y axis, which will be the primary movement direction
		 ForceCondition cond = ForceCondition.createNormalForceCondition(null, CoordinateAxis.Y, 10);

		while (true) {
			if (!robotControl.getCabinet().getExecutionService().isPaused()) {
				// move robot to right side
				tool.move(BasicMotions.lin(firstFrame).breakWhen(cond).setMode(cartImpMode).setCartVelocity(150));
				// if move to right side finished or interrupted, move back to left side
				tool.move(BasicMotions.lin(secondFrame).breakWhen(cond).setMode(cartImpMode).setCartVelocity(150));
			} else {
				break;
			}
		}

		System.exit(0);

	}

}
