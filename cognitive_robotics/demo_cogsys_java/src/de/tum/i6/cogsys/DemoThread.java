package de.tum.i6.cogsys;

import java.util.ArrayList;

import ros.NodeHandle;
import ros.Ros;
import ros.RosException;
import ros.ServiceClient;
import ros.Subscriber;
import ros.pkg.geometry_msgs.msg.Point;
import ros.pkg.gripper_control.srv.CloseGripper;
import ros.pkg.gripper_control.srv.OpenGripper;
import ros.pkg.re_speech_recognition.msg.RecognizedSpeech;
import ros.pkg.re_speech_recognition.srv.TurnOff;
import ros.pkg.re_speech_recognition.srv.TurnOn;
import ros.pkg.robot_control.srv.MoveJoints;
import ros.pkg.robot_control.srv.MoveToOS;
import ros.pkg.ros_tum_msgs.msg.Actor;
import ros.pkg.ros_tum_msgs.msg.ActorVec;

public class DemoThread implements Runnable {

	private Ros ros;
	private NodeHandle n;
	
	private Subscriber<RecognizedSpeech> subSpeech;
	private Subscriber.QueueingCallback<RecognizedSpeech> callbackSpeech;
	private ServiceClient<TurnOn.Request, TurnOn.Response, TurnOn> scton;
	private ServiceClient<TurnOff.Request, TurnOff.Response, TurnOff> sctoff;

	private Subscriber<ActorVec> sub;
	private Subscriber.QueueingCallback<ActorVec> callback;
	
	private ServiceClient<MoveToOS.Request, MoveToOS.Response, MoveToOS> scr;
	private ServiceClient<MoveJoints.Request, MoveJoints.Response, MoveJoints> scrj;

	private ServiceClient<CloseGripper.Request, CloseGripper.Response, CloseGripper> scgc;
	private ServiceClient<OpenGripper.Request, OpenGripper.Response, OpenGripper> scgo;


	private boolean running = true;

	public DemoThread(Ros ros, NodeHandle n) throws RosException {

		this.ros = ros;
		this.n = n;
		
		// subscribe to speechrec's ROS topic
		callbackSpeech = new Subscriber.QueueingCallback<RecognizedSpeech>();
		subSpeech = n.subscribe("/re_speech_recognition/output", new RecognizedSpeech(), callbackSpeech, 1);
		
		// create client for calling ROS service TurnOn (mic)
		scton = n.serviceClient("/re_speech_recognition/turn_on", new TurnOn(), false);
		// create client for calling ROS service TurnOff (mic)
		sctoff = n.serviceClient("/re_speech_recognition/turn_off", new TurnOff(), false);
		
		// subscribe to object detector's ROS topic
		callback = new Subscriber.QueueingCallback<ActorVec>();
		sub = n.subscribe("/object_detector/objects_data", new ActorVec(), callback, 1);
		// create client for calling ROS service MoveToOS
		scr = n.serviceClient("/gripperbot_control/move_to_os", new MoveToOS(), false);
		// create client for calling ROS service MoveJoints
		scrj = n.serviceClient("/gripperbot_control/move_joints", new MoveJoints(), false);
		// create client for calling ROS service CloseGripper
		scgc = n.serviceClient("/gripper_control/close_gripper", new CloseGripper(), false);
		// create client for calling ROS service OpenGripper
		scgo = n.serviceClient("/gripper_control/open_gripper", new OpenGripper(), false);

	}

	public void shutdown() {

		running = false;

	}

	protected boolean openGripper() throws RosException {

		// call gripper_control's OpenGripper ROS service
		OpenGripper.Request open = new OpenGripper.Request();

		if (!scgo.call(open).success) {
			System.out.println("Cannot open gripper!");
			return false;
		}

		return true;

	}

	protected boolean closeGripper() throws RosException {

		// call gripper_control's CloseGripper ROS service
		CloseGripper.Request open = new CloseGripper.Request();

		if (!scgc.call(open).success) {
			System.out.println("Cannot close gripper!");
			return false;
		}

		return true;

	}

	protected boolean moveRobotToHomePos() throws RosException {

		// move robot to home position 
		MoveJoints.Request rq = new MoveJoints.Request();
		rq.q0 = 0;
		rq.q1 = -0.5f;
		rq.q2 = 0;

		if (!scrj.call(rq).success) {
			System.out.println("Cannot move robot to home pos!");
			return false;
		}
		return true;

	}


	protected boolean moveRobotToOS(Point robotPosition) throws RosException {

		// call robot_control's MoveToOs ROS service in order to move 
		// the robot 
		MoveToOS.Request rq = new MoveToOS.Request();
		rq.effector = "gripper";
		rq.x = (float)(robotPosition.x);
		rq.y = (float)(robotPosition.y);
		rq.z = (float)(robotPosition.z);

		if (!scr.call(rq).success) {
			System.out.println("Cannot reach object!");
			return false;
		}
		return true;

	}

	protected boolean turnOnMic() throws RosException {

		// call re_speech_recognition's TurnOn ROS service in order to enable 
		// the mic 
		TurnOn.Request rq = new TurnOn.Request();

		if (!scton.call(rq).success) {
			System.out.println("Cannot turn on mic! Is it already on?");
			return false;
		}
		return true;

	}

	protected boolean turnOffMic() throws RosException {

		// call re_speech_recognition's TurnOff ROS service in order to disable 
		// the mic 
		TurnOff.Request rq = new TurnOff.Request();
		sctoff.call(rq);
		return true;

	}
	
	protected String getRecognizedSpeech() {

		String s = null;

		try {
			Thread.sleep(50);
		} catch (InterruptedException e) {}
		
		if (!callbackSpeech.isEmpty()) {
			try {
				s = callbackSpeech.pop().speech;
			} catch (InterruptedException e) {}	
		}
		
		return s;

	}
	
	protected ArrayList<Actor> getObjectDetections() {

		ArrayList<Actor> avl = null;
		
		try {
			Thread.sleep(50);
		} catch (InterruptedException e) {}
		
		if (!callback.isEmpty()) {
			try {
				avl = callback.pop().ActorVec;
			} catch (InterruptedException e) {}	
		}

		return avl;

	}

	protected void printObjectInfo(Actor actor) {

		// print object info
		System.out.println("Target ID: " + actor.targetId);
		System.out.println("Target type: " + actor.targetType);
		System.out.println("Target property: " + actor.targetProperty);
		// position of object in camera's global frame (in mm!)
		Point objPosition = actor.targetPoseVec.get(0).position;
		System.out.println("Target position:" +
				" x=" + objPosition.x + 
				" y=" + objPosition.y + 
				" z=" + objPosition.z);

	}

	protected Point transformObjCoordinates(Point objPos) {

		// from cam coordinate frame to robot coordinate frame
		// and from millimeters to meters
		if (objPos != null) {
			objPos.x = (715.0 - objPos.x) / 1000.0;
			objPos.y = (300.0 - objPos.y) / 1000.0;
			objPos.z = objPos.z / 1000.0;			
		}

		return objPos;

	}


	@Override
	public void run() {

		try {
			// get robot into initial state
			System.out.println("Init robot state");
			moveRobotToHomePos();
			openGripper();
			// turn on microphone
			System.out.println("Turn on mic");
			turnOnMic();

		} catch (RosException re) {
			re.printStackTrace();
			return;
		}

		// wait for spoken command
		String command = null;
		do {
			command = getRecognizedSpeech();
			if (command != null && !command.isEmpty()) {
				System.out.println("Recognized command: " + command);
			}
		} while (command == null || command.isEmpty()) ;
		
		// turn off microphone
		System.out.println("Turn off mic");
		try {
			turnOffMic();
		} catch (RosException e1) {
			e1.printStackTrace();
			return;
		}
		
		boolean pickYellow = command.indexOf("yellow") >= 0;
		
		
		while(running) {

			ArrayList<Actor> actors = getObjectDetections();
			if (actors != null && !actors.isEmpty()) {

				Actor pick = null;
				Actor place = null;
				
				// get detected objects
				for (Actor a : actors) {
					if (a.targetProperty.equalsIgnoreCase("yellow")) {
						if (pickYellow) {
							pick = a;	
						} else {
							place = a;
						}
					} else if (a.targetProperty.equalsIgnoreCase("green")) {
						if (pickYellow) {
							place = a;	
						} else {
							pick = a;
						}
					}
				}

				if (pick == null || place == null) {
					continue;
				}
				
				// print information about the detected object
				printObjectInfo(pick);
				printObjectInfo(place);

				// get position of yellow object in cam coordinate frame
				Point positionPick = pick.targetPoseVec.get(0).position;

				// transform position to robot coordinate frame
				positionPick = transformObjCoordinates(positionPick);

				// approach pose for gripper, so that we don't accidentally
				// collide with the object
				Point approachPositionPick = new Point();
				approachPositionPick.x = positionPick.x;
				approachPositionPick.y = positionPick.y;
				approachPositionPick.z = positionPick.z + 0.05; // offset in z: + 5 cm

				// get position of green object in cam coordinate frame
				Point positionPlace = place.targetPoseVec.get(0).position;

				// transform position to robot coordinate frame
				positionPlace = transformObjCoordinates(positionPlace);

				// approach pose for gripper, so that we don't accidentally
				// collide with the object
				Point approachPositionPlace = new Point();
				approachPositionPlace.x = positionPlace.x;
				approachPositionPlace.y = positionPlace.y;
				approachPositionPlace.z = positionPlace.z + 0.03; // offset in z: + 3 cm
				
				try {

					// move robot to approach pose
					moveRobotToOS(approachPositionPick);

					// move robot to grasp pose
					moveRobotToOS(positionPick);

					// call gripper_control's CloseGripper ROS service
					closeGripper();

					// move robot to approach pose
					moveRobotToOS(approachPositionPick);

					// move robot back to home position
					moveRobotToHomePos();

					// move robot to place pose
					moveRobotToOS(approachPositionPlace);					
					
					// call gripper_control's OpenGripper ROS service
					openGripper();

					// move robot back to home position
					moveRobotToHomePos();
					
				} catch (Exception e) {
					e.printStackTrace();
				} finally {
					running = false;
				}

			}
		}

		sub.shutdown();
		scr.shutdown();
		scgc.shutdown();
		scgo.shutdown();
		scton.shutdown();
		sctoff.shutdown();
		subSpeech.shutdown();

		n.shutdown();

		System.exit(0);

	}

}
