package exercises;

import robot.RobotController;

import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;
import com.kuka.roboticsAPI.conditionModel.ICondition;
import com.kuka.roboticsAPI.deviceModel.LBR;
import com.kuka.roboticsAPI.executionModel.CommandInvalidException;
import com.kuka.roboticsAPI.geometricModel.CartDOF;
import com.kuka.roboticsAPI.geometricModel.Frame;
import com.kuka.roboticsAPI.geometricModel.ObjectFrame;
import com.kuka.roboticsAPI.geometricModel.math.Transformation;
import com.kuka.roboticsAPI.motionModel.BasicMotions;
import com.kuka.roboticsAPI.motionModel.IMotionContainer;
import com.kuka.roboticsAPI.motionModel.controlModeModel.CartesianImpedanceControlMode;

import data.DataHandler;

public class Exercise4_Wireloop extends RoboticsAPIApplication {

	public static void main(String[] args) {
		// initialization
		Exercise4_Wireloop app = new Exercise4_Wireloop();
		RobotController.initialize(app);
		RobotController.createInfoGui();

		app.run();
	}

	private enum Direction {
		POSITIVE, NEGATIVE;

		public Direction invert() {
			return (this.name() == Direction.POSITIVE.name()) ? Direction.NEGATIVE : Direction.POSITIVE;
		}

		public int val() {
			return (this.name() == Direction.POSITIVE.name()) ? 1 : -1;
		}
	}

	// use this velocity for any movement that is expected to collide with obstacles
	private double lowCartVel = 50;

	// use this velocity for the movements guaranteed to not collide with anything
	private double highCartVel = 125;

	// you can use this variable to handle your approach direction  
	private Direction xDirection;

	private RobotController robotControl = null;
	private LBR robot = null;
	private ObjectFrame tool = null;

	private Frame wireloopStart = null;

	private CartesianImpedanceControlMode imp;

	@Override
	public void run() {
		robotControl = RobotController.getInstance();
		robot = robotControl.getRobot();
		tool = robotControl.getTool().getDefaultMotionFrame();

		System.out.println("Starting " + this.getClass().getSimpleName());

		// load start position [perviously teached] and define starting direction
		wireloopStart = DataHandler.loadFrame("F10").setBetaRad(0).setGammaRad(Math.PI);
		xDirection = Direction.POSITIVE;

		// configure impedance control mode
		imp = new CartesianImpedanceControlMode();
		imp.parametrize(CartDOF.TRANSL).setStiffness(1500);
		imp.parametrize(CartDOF.ROT).setStiffness(300);

		// for safety, move up
		try {
			moveUp();
		} catch (Exception e) {
			robotControl.goFront();
		}

		// move to start position in two steps: first to the position 5 cm above the start and then vertical
		Frame aboveWireloopStart = new Frame(Transformation.ofTranslation(0, 0, 50).compose(
				wireloopStart.getTransformationProvider().getTransformation()));
		tool.moveAsync((BasicMotions.ptp(aboveWireloopStart).setJointVelocityRel(0.6).setBlendingCart(10)));
		tool.move(BasicMotions.lin(wireloopStart).setCartVelocity(150));

		// insert code to move along the course here
		ICondition cond = RobotController.createJointTorqueCondition(0.05);
		int xValue = -50;
		boolean rotated = true;
		while (true) {
			try {
				// Move tip forward. Rotate clockwise if there was a collision.
				if (rotated == true)
					xValue = -50;
				else
					xValue = 50;
				
				IMotionContainer imc = tool.moveAsync(BasicMotions.linRel(xValue,0,0,tool).breakWhen(cond).setMode(imp).setCartVelocity(150).setBlendingCart(1));
				IMotionContainer imc2 = tool.move(BasicMotions.linRel(xValue,0,0,tool).breakWhen(cond).setMode(imp).setCartVelocity(150));
				
				if (imc.hasFired(cond)) {
					rotateClockwise();
					xValue = 50;
				}
			} catch(CommandInvalidException e) {
				System.out.println(e.getMessage());
				moveUp();
				rotated = !rotated;
				rotateMinus180Degree();
				moveDown();
			}
			
		}
	}

	private void moveUp() {
		tool.move(BasicMotions.linRel(0, 0, 40, robot.getRootFrame()).setCartVelocity(150));
	}

	private void moveDown() {
		tool.move(BasicMotions.linRel(0, 0, -40, robot.getRootFrame()).setCartVelocity(150));
	}
	
	private void rotateClockwise() {
		tool.move(BasicMotions.linRel(0, 0, 0, Math.toRadians(45), 0, 0, tool));
	}
	
	private void rotateMinus180Degree() {
		tool.move(BasicMotions.linRel(0, 0, 0, Math.toRadians(-180), 0, 0, tool));
	}

}
