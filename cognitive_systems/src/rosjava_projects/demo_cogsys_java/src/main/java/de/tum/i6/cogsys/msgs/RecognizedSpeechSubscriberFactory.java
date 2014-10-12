package de.tum.i6.cogsys.msgs;

import java.util.Vector;

import org.ros.message.MessageListener;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Subscriber;
import org.smerobotics.util.msg.SubscriberFactory;

import speech_recognition_msgs.RecognizedSpeech;


public class RecognizedSpeechSubscriberFactory extends SubscriberFactory {

	public static final String topic = "/speech_recognition/output";

	protected Subscriber<RecognizedSpeech> subscriber;
	
	protected Vector<RecognizedSpeech> utterances = new Vector<RecognizedSpeech>();

	public boolean hasMoreRecognizedSpeech() {
		return utterances.size() > 0;
	}

	public RecognizedSpeech getNextRecognizedSpeech() {
		return utterances.remove(0);
	}
	
	@Override
	public void addSubscribers(ConnectedNode connectedNode) {

		if (subscriber == null) {

			subscriber = connectedNode.newSubscriber(topic, RecognizedSpeech._TYPE);
			subscriber.addMessageListener(new MessageListener<RecognizedSpeech>() {
				@Override
				public void onNewMessage(RecognizedSpeech message) {

					utterances.add(message);

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
