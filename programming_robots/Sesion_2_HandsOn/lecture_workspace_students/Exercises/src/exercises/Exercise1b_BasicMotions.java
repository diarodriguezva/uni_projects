package exercises;

import java.util.Vector;

import robot.RobotController;

import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;
import com.kuka.roboticsAPI.deviceModel.JointPosition;
import com.kuka.roboticsAPI.deviceModel.Robot;
import com.kuka.roboticsAPI.geometricModel.Frame;
import com.kuka.roboticsAPI.geometricModel.Tool;
import com.kuka.roboticsAPI.motionModel.BasicMotions;
import com.kuka.roboticsAPI.motionModel.MotionBatch;
import com.kuka.roboticsAPI.motionModel.RobotMotion;

import data.DataHandler;

public class Exercise1b_BasicMotions extends RoboticsAPIApplication {

	public static void main(String[] args) {
		// initialization
		Exercise1b_BasicMotions app = new Exercise1b_BasicMotions();
		RobotController.initialize(app);

		app.run();
	}

	RobotController controller;
	Tool tool;
	Robot robot;

	@Override
	public void run() {
		controller = RobotController.getInstance();
		tool = controller.getTool();
		robot = controller.getRobot();

		System.out.println("Starting " + this.getClass().getSimpleName());

		// load saved Frames and JointPositons with the DataHandler class
		Data.init();
		
		RobotController.getInstance().goFront();
		
		

		// PTP movements to frames can be executed using different ObjectFrames. Two of these are the LBR class and the
		// Tool class. Using robot.move(Frame) will move the flange of the robot to the target frame while using
		// tool.move(Frame) will move the tcp of the tool to the target frame.
//		System.out.println("Moving to F0");
//		tool.move(BasicMotions.ptp(frames[0]));
//		
//		System.out.println("Moving to J3");
//		tool.move(BasicMotions.ptp(jointPositions[3]));
		
		
		
		

		// PTP movements with blending, movements are async to that blending is possible
//		double blendingRadiusJoints = 0.1;
//		System.out.println("Moving to F2/F4 with blending");
//		tool.moveAsync(BasicMotions.ptp(Data.frames[2]).setBlendingRel(blendingRadiusJoints));
//		blendingRadiusJoints = 0.9;
//		tool.moveAsync(BasicMotions.ptp(Data.frames[4]).setBlendingRel(blendingRadiusJoints));
		
		
		
		

		// LIN movements with blending
//		System.out.println("Moving LIN to F3 without blending");
//		tool.move(BasicMotions.lin(Data.frames[3]));
//
//		System.out.println("Moving LIN to F2 with blending");
//		double blendingRadiusCart = 10;
//		tool.moveAsync(BasicMotions.lin(Data.frames[2]).setBlendingCart(blendingRadiusCart));
		
		
//		tool.move(BasicMotions.linRel(100, 0, 0, robot.getRootFrame()));
//		tool.move(BasicMotions.linRel(0, 0, 100, robot.getRootFrame()));
//		tool.move(BasicMotions.linRel(0, 0, -200, robot.getRootFrame()));
//		tool.move(BasicMotions.linRel(0, 0, 100, robot.getRootFrame()));
		
		

		// create a motion batch movement
//		 Vector<RobotMotion<?>> motionVector = new Vector<RobotMotion<?>>();
//		 double blendingRadiusCart = 100;
//		 motionVector.add(BasicMotions.linRel(100, 0, 0, robot.getRootFrame()));
//		 motionVector.add(BasicMotions.linRel(-100, 100, 0, robot.getRootFrame()));
//		 motionVector.add(BasicMotions.linRel(-100, -100, 0, robot.getRootFrame()));
//		 motionVector.add(BasicMotions.linRel(100, -100, 0, robot.getRootFrame()));
//		 motionVector.add(BasicMotions.linRel(100, 100, 0, robot.getRootFrame()));
//		 motionVector.add(BasicMotions.linRel(-100, 0, 0, robot.getRootFrame()));
//		 
//		 RobotMotion<?>[] motionArray = motionVector.toArray(new RobotMotion<?>[motionVector.size()]);
//		 MotionBatch mb = new MotionBatch(motionArray);
//		 // set parameters for mb
//		 mb.setBlendingCart(blendingRadiusCart);
//		 System.out.println("Executing motion batch now");
//		 tool.move(mb);
		 
		
		
		
		

		// move to a joint position
		System.out.println("Moving to JointPosition J5");
		tool.move(BasicMotions.ptp(Data.jointPositions[5]));
		System.out.println("Moving to JointPosition J6");
		tool.move(BasicMotions.ptp(Data.jointPositions[6]));
		System.out.println("Moving back to Frame F5");
		// Information in frame = position of tip != configurations of all joints
		// -> minimize movement without further information on joints (frame has no redundant information)
		tool.move(BasicMotions.ptp(Data.frames[5]));

		System.exit(0);
	}
}
