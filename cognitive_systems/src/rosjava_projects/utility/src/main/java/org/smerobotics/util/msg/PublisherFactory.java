package org.smerobotics.util.msg;

import org.ros.node.ConnectedNode;

public abstract class PublisherFactory {

	public abstract void addPublishers(ConnectedNode connectedNode);

	public abstract void removePublishers();
	
}
