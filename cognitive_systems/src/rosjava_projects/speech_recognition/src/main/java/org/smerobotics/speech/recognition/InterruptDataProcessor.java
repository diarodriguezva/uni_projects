package org.smerobotics.speech.recognition;

import edu.cmu.sphinx.frontend.BaseDataProcessor;
import edu.cmu.sphinx.frontend.Data;
import edu.cmu.sphinx.frontend.DataProcessingException;

public class InterruptDataProcessor extends BaseDataProcessor {
	
	protected volatile boolean interrupt = false;

	@Override
	public Data getData() throws DataProcessingException {
		
		if (interrupt) {
			throw new RuntimeException("Interrupter is enabled!");
		}			
			
		return getPredecessor().getData();			
		
	}
	
	public synchronized void enable() {
		interrupt = true;
	}

	public synchronized void disable() {
		interrupt = false;
	}
	
	public synchronized boolean isEnabled() {
		return interrupt;
	}
	
}
