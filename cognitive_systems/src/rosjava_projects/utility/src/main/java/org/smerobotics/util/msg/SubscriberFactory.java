package org.smerobotics.util.msg;

import org.ros.node.ConnectedNode;

public abstract class SubscriberFactory {

	public abstract void addSubscribers(ConnectedNode connectedNode);
	
	public abstract void removeSubscribers();
	
}
