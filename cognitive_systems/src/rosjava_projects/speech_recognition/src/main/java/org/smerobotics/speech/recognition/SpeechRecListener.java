package org.smerobotics.speech.recognition;

public interface SpeechRecListener {

	public void resultCallback(String text, float score); // TODO start time + duration
	
}
