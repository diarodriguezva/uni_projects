package de.tum.i6.cogsys;

import ros.NodeHandle;
import ros.Ros;

public class Demo {

	private static DemoThread dt;
	
	public static Ros init() {
		
		// Initialize rosjava 
		Ros ros = Ros.getInstance();
		ros.init("demo_gripperbot");

		// Create a NodeHandle
		NodeHandle n = ros.createNodeHandle();

		// Load modules providing specific functionalities 
		try {

			dt = new DemoThread(ros, n);

		} catch (Exception e) {

			ros.logFatal("Fatal error occurred. Shutting down!");	
			
			if (n != null) {
				n.shutdown();	
			}
			
			e.printStackTrace();
			return null;
			
		}
		
		return ros;
		
	}
	
	public static void main(String[] args) {

		Ros ros = init();
		if (ros != null) {
			new Thread(dt).start();
			System.out.println("Startup complete!");
			ros.spin();
			dt.shutdown();
		}
		
	}

}
