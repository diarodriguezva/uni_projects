package de.tum.i6.cogsys.msgs;

import java.util.Vector;

import org.ros.message.MessageListener;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Subscriber;
import org.smerobotics.util.msg.SubscriberFactory;

import actor_msgs.ActorVec;


public class DetectedObjectsSubscriberFactory extends SubscriberFactory {

	public static final String topic = "/object_detector/objects_data";

	protected Subscriber<ActorVec> subscriber;
	
	protected Vector<ActorVec> detectedObjects = new Vector<ActorVec>(1);

	public ActorVec getDetectedObjects() {
		
		ActorVec actors = null;
		
		synchronized (detectedObjects) {

			if (detectedObjects.size()>0) {
				actors = detectedObjects.get(0);
			}
			
		}

		return actors;
		
	}

	@Override
	public void addSubscribers(ConnectedNode connectedNode) {

		if (subscriber == null) {

			detectedObjects.setSize(1);
			
			subscriber = connectedNode.newSubscriber(topic, ActorVec._TYPE);
			subscriber.addMessageListener(new MessageListener<ActorVec>() {
				@Override
				public void onNewMessage(ActorVec message) {

					detectedObjects.set(0, message);

				}
			});

		}

	}

	@Override
	public void removeSubscribers() {

		if (subscriber != null) {
			subscriber.shutdown();
			subscriber = null;
		}

	}

}
