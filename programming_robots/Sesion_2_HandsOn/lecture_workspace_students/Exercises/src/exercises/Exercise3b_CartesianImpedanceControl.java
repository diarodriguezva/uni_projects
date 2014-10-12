package exercises;

import robot.RobotController;

import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;
import com.kuka.roboticsAPI.geometricModel.CartDOF;
import com.kuka.roboticsAPI.geometricModel.Frame;
import com.kuka.roboticsAPI.geometricModel.Tool;
import com.kuka.roboticsAPI.motionModel.BasicMotions;
import com.kuka.roboticsAPI.motionModel.IMotionContainer;
import com.kuka.roboticsAPI.motionModel.controlModeModel.CartesianImpedanceControlMode;

public class Exercise3b_CartesianImpedanceControl extends RoboticsAPIApplication {

	public static void main(String[] args) {
		// initialization
		Exercise3b_CartesianImpedanceControl app = new Exercise3b_CartesianImpedanceControl();
		RobotController.initialize(app);
		RobotController.createInfoGui();

		app.run();
	}

	RobotController robotControl;
	Tool tool;

	@Override
	public void run() {
		robotControl = RobotController.getInstance();
		tool = robotControl.getTool();
		System.out.println("Starting " + this.getClass().getSimpleName());

		// move robot into a crane position and save position as target frame
		RobotController.getInstance().goFront();
		Frame currentFrame = robotControl.getTcpFrame();

		// create and configure CartesianImpedanceControlMode
		CartesianImpedanceControlMode cartImpMode = new CartesianImpedanceControlMode();

		cartImpMode.parametrize(CartDOF.TRANSL).setStiffness(1500);
		cartImpMode.parametrize(CartDOF.TRANSL).setDamping(0.7);

//		cartImpMode.parametrize(CartDOF.X).setStiffness(50);
//		cartImpMode.parametrize(CartDOF.X).setDamping(0.3);
//		cartImpMode.parametrize(CartDOF.Y).setStiffness(500);
//		cartImpMode.parametrize(CartDOF.Y).setDamping(0.3);
//		cartImpMode.parametrize(CartDOF.Z).setStiffness(500);
//		cartImpMode.parametrize(CartDOF.Z).setDamping(0.8);

		cartImpMode.parametrize(CartDOF.ROT).setStiffness(200);
		cartImpMode.parametrize(CartDOF.ROT).setDamping(0.7);

		cartImpMode.setNullSpaceDamping(0.8);
		cartImpMode.setNullSpaceStiffness(0);

		cartImpMode.setMaxControlForce(30, 30, 30, 10, 10, 10, false);

		// start first movement
		IMotionContainer activeMove = tool.moveAsync(BasicMotions.lin(currentFrame).setMode(cartImpMode));
		IMotionContainer nextMove = null;

		// always create a new movement to the target position before the active movement is finished and then wait for
		// the active movement to finish
		while (true) {
			if (!robotControl.getCabinet().getExecutionService().isPaused()) {
				nextMove = tool.moveAsync(BasicMotions.lin(currentFrame).setMode(cartImpMode));
				activeMove.await();
				activeMove = nextMove;
			} else {
				break;
			}
		}

		System.exit(0);

	}

}
