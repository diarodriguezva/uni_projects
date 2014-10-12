package org.smerobotics.util.srv;

import org.ros.node.ConnectedNode;

public abstract class ServiceResponseBuilderFactory {
	
	public abstract void addServiceServers(ConnectedNode connectedNode);
	
	public abstract void removeServiceServers();

	public static void advertiseServices(
			ConnectedNode connectedNode, 
			ServiceResponseBuilderFactory[] serviceBuilders) {
		
		for (ServiceResponseBuilderFactory f : serviceBuilders) {
			f.addServiceServers(connectedNode);
		}
		
	}
	
	public static void shutdownServiceClients(
			ServiceResponseBuilderFactory[] serviceBuilders) {
		
		for (ServiceResponseBuilderFactory f : serviceBuilders) {
			f.removeServiceServers();
		}
		
	}
	
}
