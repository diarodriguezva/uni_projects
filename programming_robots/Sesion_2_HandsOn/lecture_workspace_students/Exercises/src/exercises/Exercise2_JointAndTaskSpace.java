package exercises;

import java.util.Vector;

import robot.RobotController;

import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;
import com.kuka.roboticsAPI.deviceModel.JointPosition;
import com.kuka.roboticsAPI.deviceModel.LBR;
import com.kuka.roboticsAPI.geometricModel.Frame;
import com.kuka.roboticsAPI.geometricModel.Tool;
import com.kuka.roboticsAPI.motionModel.BasicMotions;
import com.kuka.roboticsAPI.motionModel.MotionBatch;
import com.kuka.roboticsAPI.motionModel.RobotMotion;

import data.DataHandler;
import data.FileLogger;
import data.FileLogger.Fields;

public class Exercise2_JointAndTaskSpace extends RoboticsAPIApplication {

	public static void main(String[] args) {
		// initialization
		Exercise2_JointAndTaskSpace app = new Exercise2_JointAndTaskSpace();
		RobotController.initialize(app);

		app.run();
	}

	RobotController controller;
	LBR robot;
	Tool tool;

	@Override
	public void run() {
		controller = RobotController.getInstance();
		robot = controller.getRobot();
		tool = controller.getTool();

		System.out.println("Starting " + this.getClass().getSimpleName());

		double blendingRadiusCart = 10;

		// load previously teached frames and joint positions
		Data.init();
				

		// create a motion batch with PTP movements -> Joints
		Vector<RobotMotion<?>> motionVector = new Vector<RobotMotion<?>>();
		motionVector.add(BasicMotions.ptp(Data.jointPositions[7]));
		motionVector.add(BasicMotions.ptp(Data.jointPositions[8]));
		motionVector.add(BasicMotions.ptp(Data.jointPositions[9]));
		RobotMotion<?>[] motionArray = motionVector.toArray(new RobotMotion<?>[motionVector.size()]);
		MotionBatch mb_PTP = new MotionBatch(motionArray);
		// set parameters for mb
		mb_PTP.setBlendingCart(blendingRadiusCart);
		mb_PTP.setJointVelocityRel(0.2);
		
		
		// create a logger to write data to a log file every 100 ms
		FileLogger fl_PTP = new FileLogger(100, Fields.TIME, Fields.TRANSLATIONAL_DISTANCE,
		Fields.ROTATIONAL_DISTANCE,
		Fields.JOINT_SPACE_DISTANCE);
		fl_PTP.setFilename("log_PTP_movement");
		
		

		// use a sync move to the first position, then start logging and execute the motion batch
		RobotController.getInstance().goFront();
		fl_PTP.startLogging();
		tool.move(mb_PTP);
		fl_PTP.stopLogging();
		
		
		
		

		// create a motion batch with LIN movements -> Frames
		RobotController.getInstance().goFront();
		
		motionVector = new Vector<RobotMotion<?>>();
		motionVector.add(BasicMotions.lin(Data.frames[7]));
		motionVector.add(BasicMotions.lin(Data.frames[8]));
		motionVector.add(BasicMotions.lin(Data.frames[9]));
		motionArray = motionVector.toArray(new RobotMotion<?>[motionVector.size()]);
		MotionBatch mb_LIN = new MotionBatch(motionArray);
		// set parameters for mb
		mb_LIN.setBlendingCart(blendingRadiusCart);
		mb_LIN.setJointVelocityRel(0.2);
				
		
		// create a logger to write data to a log file every 100 ms
		FileLogger fl_LIN = new FileLogger(100, Fields.TIME, Fields.TRANSLATIONAL_DISTANCE,
		Fields.ROTATIONAL_DISTANCE,
		Fields.JOINT_SPACE_DISTANCE);
		fl_LIN.setFilename("log_LIN_movement");
		
		// start logging and execute the motion batch
		RobotController.getInstance().goFront();
		fl_LIN.startLogging();
		tool.move(mb_LIN);
		fl_LIN.stopLogging();

		System.exit(0);
	}

}
