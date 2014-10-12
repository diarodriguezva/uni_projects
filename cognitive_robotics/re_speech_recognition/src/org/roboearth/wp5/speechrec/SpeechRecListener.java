package org.roboearth.wp5.speechrec;

public interface SpeechRecListener {

	public void resultCallback(String text, float score); // TODO start time + duration
	
}
