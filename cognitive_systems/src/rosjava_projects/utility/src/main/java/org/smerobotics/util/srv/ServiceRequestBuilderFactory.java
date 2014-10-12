package org.smerobotics.util.srv;

import org.ros.node.ConnectedNode;

public abstract class ServiceRequestBuilderFactory {

	public abstract void addServiceClients(ConnectedNode connectedNode);
	
	public abstract void removeServiceClients();
	
	public static void createServiceClients(
			ConnectedNode connectedNode,
			ServiceRequestBuilderFactory[] serviceClientBuilders) {
		
		for (ServiceRequestBuilderFactory f : serviceClientBuilders) {
			f.addServiceClients(connectedNode);
		}
		
	}

	public static void shutdownServiceClients(
			ServiceRequestBuilderFactory[] serviceClientBuilders) {
		
		for (ServiceRequestBuilderFactory f : serviceClientBuilders) {
			f.removeServiceClients();
		}
		
	}
	
}
