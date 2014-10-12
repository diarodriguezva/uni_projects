package exercises;

import com.kuka.roboticsAPI.deviceModel.JointPosition;
import com.kuka.roboticsAPI.geometricModel.Frame;

import data.DataHandler;

public class Data {

	public static int NUM_RECORDS = 11;
	public static Frame[] frames;
	public static JointPosition[] jointPositions;
	
	public static void init() {
		// load saved Frames and JointPositons with the DataHandler class
				frames = new Frame[NUM_RECORDS];
				jointPositions = new JointPosition[NUM_RECORDS];
				for (int i = 0; i < NUM_RECORDS; i++) {
					frames[i] = DataHandler.loadFrame("F" + i);
					jointPositions[i] = DataHandler.loadJointPos("J" + i);
				}
	}
	
}