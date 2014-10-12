package robot;

import java.awt.Color;
import java.awt.ComponentOrientation;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.border.Border;

import com.kuka.roboticsAPI.deviceModel.LBR;
import com.kuka.roboticsAPI.geometricModel.Frame;
import com.kuka.roboticsAPI.sensorModel.ForceSensorData;
import com.kuka.roboticsAPI.sensorModel.SensorForExternalForce;

public class InfoGUI {
	
	private int xPosition = 700;
	private int yPosition = 200;

	private List<JProgressBar> torqueBarsInt = new ArrayList<JProgressBar>();
	private List<JProgressBar> torqueBarsExt = new ArrayList<JProgressBar>();
	private List<JProgressBar> wrenchBarsTcp = new ArrayList<JProgressBar>();

	private List<JLabel> torqueValuesExt = new ArrayList<JLabel>();
	private List<JLabel> torqueValuesInt = new ArrayList<JLabel>();
	private List<JLabel> wrenchValuesTcp = new ArrayList<JLabel>();

	private List<JLabel> positionsTcp = new ArrayList<JLabel>();

	private Thread updateThread;

	private void configureGui() {
		// UIManager.setLookAndFeel("javax.swing.plaf.metal.MetalLookAndFeel");

		JFrame mainFrame = new JFrame();

		// make sure the program exits when the frame closes
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.setTitle("RobotInfo");
		mainFrame.setSize(800, 400);
		mainFrame.setLayout(new GridBagLayout());

		// This will center the JFrame in the middle of the screen
		mainFrame.setLocationRelativeTo(null);
		mainFrame.setLocation(xPosition, yPosition);

		JPanel torquePanel = new JPanel();
		Border torqueBorder = BorderFactory.createTitledBorder("Joint Torques [Nm]");
		torquePanel.setBorder(torqueBorder);
		mainFrame.add(torquePanel, new GridBagConstraints(0, 0, 1, 7, 1, 1, GridBagConstraints.CENTER,
				GridBagConstraints.BOTH, new Insets(2, 2, 2, 2), 0, 0));

		GridBagLayout layout = new GridBagLayout();
		torquePanel.setLayout(layout);

		// constraint settings
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.weightx = 1;
		gbc.weighty = 1;
		gbc.fill = GridBagConstraints.BOTH;
		gbc.insets = new Insets(2, 0, 2, 0);

		Color colorInt = new Color(0, 110, 0);
		Color colorExt = new Color(230, 110, 0);
		Color colorBg = Color.WHITE;
		int fontSize = 13;

		gbc.gridy = 0;
		for (int i = 0; i < 7; i++) {
			gbc.insets = new Insets(0, 0, 0, 0);

			JLabel jointNumber = new JLabel();
			jointNumber.setText("T" + (i + 1) + ":");
			jointNumber.setFont(new Font("Courier New", Font.BOLD, fontSize));
			gbc.gridheight = 2;
			gbc.weightx = 0;
			gbc.insets = new Insets(6, 0, 0, 10);
			torquePanel.add(jointNumber, gbc);
			gbc.gridheight = 1;
			gbc.weightx = 1;
			gbc.insets = new Insets(6, 0, 0, 0);

			JProgressBar int_neg = new JProgressBar();
			int_neg.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
			int_neg.setForeground(colorInt);
			torquePanel.add(int_neg, gbc);
			torqueBarsInt.add(int_neg);

			JProgressBar int_pos = new JProgressBar();
			int_pos.setForeground(colorInt);
			torquePanel.add(int_pos, gbc);
			torqueBarsInt.add(int_pos);

			JLabel intVal = new JLabel();
			intVal.setFont(new Font("Courier New", Font.PLAIN, fontSize));
			gbc.weightx = 0;
			gbc.insets = new Insets(6, 10, 0, 10);
			torquePanel.add(intVal, gbc);
			gbc.weightx = 1;
			torqueValuesInt.add(intVal);

			gbc.gridy += 1;
			gbc.insets = new Insets(0, 0, 6, 0);

			JProgressBar ext_neg = new JProgressBar();
			ext_neg.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
			ext_neg.setForeground(colorExt);
			torquePanel.add(ext_neg, gbc);
			torqueBarsExt.add(ext_neg);

			JProgressBar ext_pos = new JProgressBar();
			ext_pos.setForeground(colorExt);
			torquePanel.add(ext_pos, gbc);
			torqueBarsExt.add(ext_pos);

			JLabel extVal = new JLabel();
			extVal.setFont(new Font("Courier New", Font.PLAIN, fontSize));
			gbc.weightx = 0;
			gbc.insets = new Insets(0, 10, 0, 10);
			torquePanel.add(extVal, gbc);
			gbc.weightx = 1;
			torqueValuesExt.add(extVal);

			int_neg.setStringPainted(true);
			int_pos.setStringPainted(true);
			ext_neg.setStringPainted(true);
			ext_pos.setStringPainted(true);

			int_neg.setBackground(colorBg);
			int_pos.setBackground(colorBg);
			ext_neg.setBackground(colorBg);
			ext_pos.setBackground(colorBg);

			gbc.gridy += 1;
		}

		// tcp torque panel
		JPanel tcpTorquePanel = new JPanel();
		Border tcpBorder = BorderFactory.createTitledBorder("TCP Torques [Nm]");
		tcpTorquePanel.setBorder(tcpBorder);
		mainFrame.add(tcpTorquePanel, new GridBagConstraints(1, 0, 1, 3, 1, 3, GridBagConstraints.CENTER,
				GridBagConstraints.BOTH, new Insets(2, 2, 2, 2), 0, 0));

		layout = new GridBagLayout();
		tcpTorquePanel.setLayout(layout);

		// constraint settings
		gbc = new GridBagConstraints();
		gbc.weightx = 1;
		gbc.weighty = 1;
		gbc.fill = GridBagConstraints.BOTH;
		gbc.insets = new Insets(2, 0, 2, 0);

		gbc.gridy = 0;
		String[] tcpTorqueLabels = { "TX", "TY", "TZ" };
		for (int i = 0; i < 3; i++) {
			gbc.insets = new Insets(0, 0, 0, 0);

			JLabel jointNumber = new JLabel();
			jointNumber.setText(tcpTorqueLabels[i] + ":");
			jointNumber.setFont(new Font("Courier New", Font.BOLD, fontSize));
			gbc.weightx = 0;
			gbc.insets = new Insets(6, 0, 0, 10);
			tcpTorquePanel.add(jointNumber, gbc);
			gbc.weightx = 1;
			gbc.insets = new Insets(6, 0, 0, 0);

			JProgressBar int_neg = new JProgressBar();
			int_neg.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
			int_neg.setForeground(colorInt);
			tcpTorquePanel.add(int_neg, gbc);
			wrenchBarsTcp.add(int_neg);

			JProgressBar int_pos = new JProgressBar();
			int_pos.setForeground(colorInt);
			tcpTorquePanel.add(int_pos, gbc);
			wrenchBarsTcp.add(int_pos);

			JLabel intVal = new JLabel();
			intVal.setFont(new Font("Courier New", Font.PLAIN, fontSize));
			gbc.weightx = 0;
			gbc.insets = new Insets(6, 10, 0, 10);
			tcpTorquePanel.add(intVal, gbc);
			gbc.weightx = 1;
			wrenchValuesTcp.add(intVal);

			int_neg.setStringPainted(true);
			int_pos.setStringPainted(true);

			int_neg.setBackground(colorBg);
			int_pos.setBackground(colorBg);

			gbc.gridy += 1;
		}

		// tcp force panel
		JPanel tcpForcePanel = new JPanel();
		tcpForcePanel.setBorder(BorderFactory.createTitledBorder("TCP Forces [N]"));
		mainFrame.add(tcpForcePanel, new GridBagConstraints(1, 3, 1, 3, 1, 3, GridBagConstraints.CENTER,
				GridBagConstraints.BOTH, new Insets(2, 2, 2, 2), 0, 0));

		layout = new GridBagLayout();
		tcpForcePanel.setLayout(layout);

		// constraint settings
		gbc = new GridBagConstraints();
		gbc.weightx = 1;
		gbc.weighty = 1;
		gbc.fill = GridBagConstraints.BOTH;
		gbc.insets = new Insets(2, 0, 2, 0);

		gbc.gridy = 0;
		String[] tcpForceLabels = { "FX", "FY", "FZ" };
		for (int i = 0; i < 3; i++) {
			gbc.insets = new Insets(0, 0, 0, 0);

			JLabel jointNumber = new JLabel();
			jointNumber.setText(tcpForceLabels[i] + ":");
			jointNumber.setFont(new Font("Courier New", Font.BOLD, fontSize));
			gbc.weightx = 0;
			gbc.insets = new Insets(6, 0, 0, 10);
			tcpForcePanel.add(jointNumber, gbc);
			gbc.weightx = 1;
			gbc.insets = new Insets(6, 0, 0, 0);

			JProgressBar int_neg = new JProgressBar();
			int_neg.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
			int_neg.setForeground(colorInt);
			tcpForcePanel.add(int_neg, gbc);
			wrenchBarsTcp.add(int_neg);

			JProgressBar int_pos = new JProgressBar();
			int_pos.setForeground(colorInt);
			tcpForcePanel.add(int_pos, gbc);
			wrenchBarsTcp.add(int_pos);

			JLabel intVal = new JLabel();
			intVal.setFont(new Font("Courier New", Font.PLAIN, fontSize));
			gbc.weightx = 0;
			gbc.insets = new Insets(6, 10, 0, 10);
			tcpForcePanel.add(intVal, gbc);
			gbc.weightx = 1;
			wrenchValuesTcp.add(intVal);

			int_neg.setStringPainted(true);
			int_pos.setStringPainted(true);

			int_neg.setBackground(colorBg);
			int_pos.setBackground(colorBg);

			gbc.gridy += 1;
		}

		// dummy label
		// mainFrame.add(new JLabel("Dummy Label"), new GridBagConstraints(1, 6, 1, 1, 1, 1, GridBagConstraints.CENTER,
		// GridBagConstraints.BOTH, new Insets(2, 2, 2, 2), 0, 0));

		// position panel
		JPanel positionPanel = new JPanel();
		positionPanel.setBorder(BorderFactory.createTitledBorder("TCP Position [mm] / Orientation [deg]"));
		mainFrame.add(positionPanel, new GridBagConstraints(1, 6, 1, 1, 1, 2, GridBagConstraints.CENTER,
				GridBagConstraints.BOTH, new Insets(2, 2, 2, 2), 0, 0));

		layout = new GridBagLayout();
		positionPanel.setLayout(layout);

		// constraint settings
		gbc = new GridBagConstraints();
		gbc.weightx = 1;
		gbc.weighty = 1;
		gbc.fill = GridBagConstraints.BOTH;
		gbc.insets = new Insets(2, 0, 2, 0);

		String[] tcpCoordLabels = { "X", "Y", "Z", "A", "B", "C" };
		gbc.gridy = 0;
		gbc.gridx = 0;
		for (int i = 0; i < 6; i++) {
			JLabel coordinateLabel = new JLabel();
			coordinateLabel.setText(tcpCoordLabels[i] + ":");
			coordinateLabel.setFont(new Font("Courier New", Font.BOLD, fontSize));
			gbc.weightx = 0;
			gbc.insets = new Insets(6, 0, 0, 10);
			positionPanel.add(coordinateLabel, gbc);
			gbc.weightx = 1;
			gbc.insets = new Insets(6, 0, 0, 0);

			JLabel value = new JLabel();
			value.setText("500");
			value.setFont(new Font("Courier New", Font.PLAIN, fontSize));
			gbc.weightx = 0;
			gbc.insets = new Insets(6, 0, 0, 10);
			gbc.gridx += 1;
			positionPanel.add(value, gbc);
			gbc.weightx = 1;
			gbc.gridx -= 1;
			gbc.insets = new Insets(6, 0, 0, 0);
			positionsTcp.add(value);

			gbc.gridy += 1;
			if (i == 2) {
				gbc.gridx += 2;
				gbc.gridy = 0;
			}
		}

		// make sure the JFrame is visible
		mainFrame.setVisible(true);
	}

	public void connectGui() {

	}

	private SensorForExternalForce sensorForceExt = RobotController.getInstance().getRobot()
			.getSensorForExternalForce();
	private ForceSensorData extForce;

	private RobotController controller = RobotController.getInstance();
	private LBR robot = controller.getRobot();

	public InfoGUI() {

		configureGui();
		connectGui();

		this.updateThread = new Thread(new Runnable() {

			@Override
			public void run() {

				long start = System.currentTimeMillis();
				long now = start;
				long next = start;

				double[] measuredTorque = null;
				double[] extTorque = null;
				double[] extForceD = new double[6];

				Frame tcpFrame = null;
				double[] tcpFrameD = new double[6];

				DecimalFormat fmt = new DecimalFormat("+#,000.00;-#");

				while (true) {
					try {
						now = System.currentTimeMillis();
						next += 100;

						// internal torques
						measuredTorque = robot.getMeasuredTorque().getTorqueValues();

						for (int i = 0; i < 7; i++) {
							if (measuredTorque[i] < 0) {
								torqueBarsInt.get(2 * i).setValue(
										(int) (-1 * measuredTorque[i] / RobotController.MAX_JOINT_TORQUES[i] * 100));
								torqueBarsInt.get(2 * i + 1).setValue(0);
							} else {
								torqueBarsInt.get(2 * i).setValue(0);
								torqueBarsInt.get(2 * i + 1).setValue(
										(int) (measuredTorque[i] / RobotController.MAX_JOINT_TORQUES[i] * 100));
							}
							torqueValuesInt.get(i).setText(fmt.format(measuredTorque[i]));
						}

						// external torques
						extTorque = robot.getExternalTorque().getTorqueValues();

						for (int i = 0; i < 7; i++) {
							if (extTorque[i] < 0) {
								torqueBarsExt.get(2 * i).setValue(
										(int) (-1 * extTorque[i] / RobotController.MAX_JOINT_TORQUES[i] * 100));
								torqueBarsExt.get(2 * i + 1).setValue(0);
							} else {
								torqueBarsExt.get(2 * i).setValue(0);
								torqueBarsExt.get(2 * i + 1).setValue(
										(int) (extTorque[i] / RobotController.MAX_JOINT_TORQUES[i] * 100));
							}
							torqueValuesExt.get(i).setText(fmt.format(extTorque[i]));
						}

						// external forces
						extForce = robot.getExternalForceTorque(controller.getTool().getDefaultMotionFrame());
						// extForce = robot.getSensorForExternalForce().getSensorData(
						// RobotController.getInstance().getTool(), new Frame(Transformation.ofDeg(0, 0, 0, 228, -90,
						// 162)));
						extForce = sensorForceExt.getSensorData();
						extForceD[0] = extForce.getTorque().getX();
						extForceD[1] = extForce.getTorque().getY();
						extForceD[2] = extForce.getTorque().getZ();
						extForceD[3] = extForce.getForce().getX();
						extForceD[4] = extForce.getForce().getY();
						extForceD[5] = extForce.getForce().getZ();

						for (int i = 0; i < 6; i++) {
							if (extForceD[i] < 0) {
								wrenchBarsTcp.get(2 * i).setValue(
										(int) (-1 * extForceD[i] / RobotController.TCP_FORCES[i] * 100));
								wrenchBarsTcp.get(2 * i + 1).setValue(0);
							} else {
								wrenchBarsTcp.get(2 * i).setValue(0);
								wrenchBarsTcp.get(2 * i + 1).setValue(
										(int) (extForceD[i] / RobotController.TCP_FORCES[i] * 100));
							}
							wrenchValuesTcp.get(i).setText(fmt.format(extForceD[i]));
						}

						// tcp position
						tcpFrame = controller.getTcpFrame();
						tcpFrameD[0] = tcpFrame.getX();
						tcpFrameD[1] = tcpFrame.getY();
						tcpFrameD[2] = tcpFrame.getZ();
						tcpFrameD[3] = tcpFrame.getAlphaRad();
						tcpFrameD[4] = tcpFrame.getBetaRad();
						tcpFrameD[5] = tcpFrame.getGammaRad();

						for (int i = 0; i < 3; i++) {
							positionsTcp.get(i).setText(fmt.format(tcpFrameD[i]));
						}

						for (int i = 3; i < 6; i++) {
							positionsTcp.get(i).setText(fmt.format(Math.toDegrees(tcpFrameD[i])));
						}

						try {
							if (next - now > 0)
								Thread.sleep(next - now);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					} catch (Exception e) {
						System.err.println(e.getMessage());
					}
				}

			}
		});
		this.updateThread.start();
	}

}
