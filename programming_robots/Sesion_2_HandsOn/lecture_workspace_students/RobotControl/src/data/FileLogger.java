package data;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.HashSet;
import java.util.Set;

import robot.RobotController;

import com.kuka.roboticsAPI.geometricModel.Frame;

public class FileLogger implements Runnable {

	/**
	 * Possible fields to be logged to a file.
	 */
	public enum Fields {
		/**
		 * Time in ms since start of logging.
		 */
		TIME,
		/**
		 * Current joint position in rad [7 values].
		 */
		JOINT_POSITION,
		/**
		 * Current tcp translation in mm [3 values].
		 */
		TRANSLATION,
		/**
		 * Current tcp orientation in deg [3 values].
		 */
		ORIENTATION,
		/**
		 * Joint space distance to the last log entry [Euclidean metric].
		 */
		JOINT_SPACE_DISTANCE,
		/**
		 * Shortest angle between current and previous log entry tcp orientations. // TODO: add unit
		 */
		ROTATIONAL_DISTANCE,
		/**
		 * Distance between current and previous log entry tcp translations [Euclidean metric].
		 */
		TRANSLATIONAL_DISTANCE
	}

	private boolean active = false;

	private boolean finished = false;

	private int intervall = 100;

	private SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd_HHmmss");

	private String filename = null;

	private Thread loggerThread = null;

	private Set<Fields> fieldsToWrite = new HashSet<Fields>();

	/**
	 * Create a file logger with given intervall and specified fields. If not set by setFilename(), the file name will be the
	 * time when starting logging.
	 * 
	 * @param intervall
	 *            time between log entries in ms.
	 * @param fields
	 *            list of fields to written to the log file. See FileLogger.Fields for reference.
	 */
	public FileLogger(int intervall, Fields... fields) {
		this.intervall = intervall;
		System.out.println("logging fields:");
		for (Fields f : fields) {
			fieldsToWrite.add(f);
			System.out.println(f.name());
		}
	}

	/**
	 * Create a file logger with given intervall and all possible fields. If not set by setFilename(), the file name will be
	 * the time when starting logging.
	 * 
	 * @param intervall
	 *            time between log entries in ms.
	 */
	public FileLogger(int intervall) {
		this.intervall = intervall;
		System.out.println("logging all fields:");
		for (Fields f : Fields.values()) {
			fieldsToWrite.add(f);
		}
	}

	/**
	 * Set the name of the log file.
	 * 
	 * @param filename
	 *            name of the file [ending .log will automatically be added]
	 */
	public void setFilename(String filename) {
		this.filename = DataHandler.DataPath + "/logs/" + filename + ".log";
	}

	/**
	 * Stop logging and disable this FileLogger instance.
	 */
	public void stopLogging() {
		active = false;
		finished = true;
	}

	/**
	 * Start logging.
	 */
	public void startLogging() {
		if (active && !finished) {
			System.err.println("Logging has already been started!");
			return;
		}
		active = true;

		File fileObject = new File(DataHandler.DataPath + "/logs/");
		fileObject.mkdirs();

		if (filename == null) {
			setFilename(sdf.format(Calendar.getInstance().getTime()));
		}

		this.loggerThread = new Thread(this);
		this.loggerThread.start();
	}

	/**
	 * Thread target run method. WILL BLOCK PRIGRAM IF CALLED MANUALLY;
	 */
	@Override
	public void run() {
		System.out.println("Starting to log to file '" + filename + "' now");

		BufferedWriter writer = null;
		try {
			writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(filename, false), "utf-8"));

			Frame tcpFrame = null;
			Frame tcpFrameLast = null;
			double[] jointPos = null;
			double[] jointPosLast = null;

			long start = System.currentTimeMillis();
			long now = start;
			long next = start + intervall;

			while (active) {
				// get data
				jointPos = RobotController.getInstance().getRobot().getCurrentJointPosition().get();
				tcpFrame = RobotController.getInstance().getTcpFrame();

				// time
				now = System.currentTimeMillis();
				if (fieldsToWrite.contains(Fields.TIME)) {
					writer.write("" + (now - start));
					writer.write("    ");
				}

				// write joint position
				if (fieldsToWrite.contains(Fields.JOINT_POSITION)) {
					for (int i = 0; i < 7; i++) {
						writer.write(" " + String.format("%.3f", jointPos[i]));
					}
					writer.write("    ");
				}

				// write tcp frame
				if (fieldsToWrite.contains(Fields.TRANSLATION)) {
					writer.write(" " + String.format("%.3f", tcpFrame.getX()));
					writer.write(" " + String.format("%.3f", tcpFrame.getY()));
					writer.write(" " + String.format("%.3f", tcpFrame.getZ()));
					writer.write("    ");
				}

				if (fieldsToWrite.contains(Fields.ORIENTATION)) {
					writer.write(" " + String.format("%.3f", tcpFrame.getAlphaRad()));
					writer.write(" " + String.format("%.3f", tcpFrame.getBetaRad()));
					writer.write(" " + String.format("%.3f", tcpFrame.getGammaRad()));
					writer.write("    ");
				}

				// write joint space distance
				if (fieldsToWrite.contains(Fields.JOINT_SPACE_DISTANCE)) {
					double dist = 0;
					if (jointPosLast != null) {
						for (int i = 0; i < jointPos.length; i++) {
							dist += Math.pow(jointPosLast[i] - jointPos[i], 2);
						}
					}
					writer.write(" " + String.format("%.5f", Math.sqrt(dist)));
					writer.write("    ");
				}

				// write translational distance
				if (fieldsToWrite.contains(Fields.TRANSLATIONAL_DISTANCE)) {
					double dist = 0;
					if (tcpFrameLast != null) {
						dist = tcpFrameLast.distanceTo(tcpFrame);
					}
					writer.write(" " + String.format("%.5f", dist));
					writer.write("    ");
				}

				// write rotational distance
				if (fieldsToWrite.contains(Fields.ROTATIONAL_DISTANCE)) {
					double dist = 0;
					if (tcpFrameLast != null) {
						dist = tcpFrameLast.rotationalDistanceTo(tcpFrame);
					}
					writer.write(" " + String.format("%.5f", dist));
					// writer.write("    ");
				}

				// end line
				writer.write("\n");
				try {
					Thread.sleep(next - System.currentTimeMillis());
				} catch (InterruptedException e) {
					// e.printStackTrace();
					System.err.println(e.getMessage());
				}
				next += intervall;

				jointPosLast = jointPos;
				tcpFrameLast = tcpFrame;
			}

		} catch (IOException e) {
			// report
		} finally {
			try {
				writer.close();
			} catch (Exception e) {
			}
		}
	}
}