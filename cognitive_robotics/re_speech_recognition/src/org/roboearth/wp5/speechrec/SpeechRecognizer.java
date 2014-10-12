package org.roboearth.wp5.speechrec;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.util.Iterator;
import java.util.StringTokenizer;
import java.util.Vector;

import org.roboearth.wp5.speechrec.ros.ROSWrapper;

import edu.cmu.sphinx.decoder.search.Token;
import edu.cmu.sphinx.frontend.util.Microphone;
import edu.cmu.sphinx.instrumentation.BestPathAccuracyTracker;
import edu.cmu.sphinx.jsgf.JSGFGrammar;
import edu.cmu.sphinx.linguist.dictionary.Dictionary;
import edu.cmu.sphinx.recognizer.Recognizer;
import edu.cmu.sphinx.result.ConfidenceResult;
import edu.cmu.sphinx.result.ConfidenceScorer;
import edu.cmu.sphinx.result.ConfusionSet;
import edu.cmu.sphinx.result.Result;
import edu.cmu.sphinx.util.LogMath;
import edu.cmu.sphinx.util.props.ConfigurationManager;


public class SpeechRecognizer {

	protected String stdGrammarFile = "example"; // without file extension (must be .gram)
	protected String configFile = "config.xml";
	protected String localPkgPath = null;
	protected String relConfigPath = "config/";
	protected String relGrammarPath = "grammar/";
	protected ConfigurationManager cm;
	protected LogMath logm;
	protected Dictionary dict;
	protected JSGFGrammar grammar;
	protected Recognizer recognizer;
	protected Microphone microphone;
	protected InterruptDataProcessor interrupter;
	protected ConfidenceScorer scorer;
	protected BestPathAccuracyTracker bptracker;
	protected volatile boolean shallRun = true;
	protected volatile boolean listen = false;
	protected volatile boolean sleeping = false;
	protected Vector<SpeechRecListener> listeners = new Vector<SpeechRecListener>();
	
	public SpeechRecognizer() {

		init();
		new SpeechRecognizerThread();

	}

	protected void init() {
		
		localPkgPath = ROSWrapper.getLocalPackagePath("re_speech_recognition");

		try {
			cm = new ConfigurationManager(localPkgPath+relConfigPath+configFile);
		} catch (Exception e) {
			System.out.println("[ERROR] Couldn't load config file 'config.xml'");
			System.exit(1);
		}

		try {
			dict = (Dictionary)cm.lookup("dictionary");
			logm = (LogMath)cm.lookup("logMath");

			grammar = new JSGFGrammar(localPkgPath+relGrammarPath, logm, 
					stdGrammarFile, false, true, false, false, dict);
			cm.addConfigurable(grammar, "jsgfGrammar");

			recognizer = (Recognizer) cm.lookup("recognizer");
			interrupter = (InterruptDataProcessor) cm.lookup("interruptDataProcessor");
			interrupter.enable();
			scorer = (ConfidenceScorer) cm.lookup("confidenceScorer");

			microphone = (Microphone) cm.lookup("microphone");

			bptracker = (BestPathAccuracyTracker) cm.lookup("accuracyTracker"); // TODO 
			
			
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
		
		try {
			recognizer.allocate();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("[ERROR] Couldn't allocate recognizer");
			System.exit(1);
		}
		
	}

	protected String getGrammerName(String jsgfGrammar) {
		
		String name = null;
		
		StringTokenizer st = new StringTokenizer(jsgfGrammar, "\n; ");
		while (st.hasMoreTokens()) {
			String t = st.nextToken().trim();
			if (t.equals("grammar") && st.hasMoreTokens()) {
				name = st.nextToken();
				break;
			}
		}
		
		return name;
		
	}
	
	protected static boolean writeFile(String content, File file) {

		boolean ok = false;
		
		BufferedWriter bw = null;
		try {
			FileWriter fw = new FileWriter(file);
			bw = new BufferedWriter(fw);
			bw.write(content);
			ok = true;
		} catch (Exception e) {
			System.out.println("[ERROR] Couldn't write to file '" + 
					file.getAbsolutePath() + "'");
		} finally {
			if (bw != null) {
				try {
					bw.close();
				} catch (Exception e) {}
			}
		}

		return ok;
		
	}
	
	public synchronized boolean turnOnMic() {

		boolean ok = false;
		
		if (!listen) {
			
			synchronized (interrupter) {
				
				while (!sleeping) {
					try {
						interrupter.wait();
					} catch (InterruptedException e) {}
				}
				
				if (ok = microphone.startRecording()) {
					interrupter.disable();
					System.out.println("[INFO] Enabled listening to microphone");
					interrupter.notifyAll();
					listen = true;
				} else {
					System.out.println("[ERROR] Couldn't start microphone");
				}
				
			}
		
		} else {
			
			System.out.println("[WARNING] Received 'TurnOn' request " +
					"despite already listening to microphone");
			
		}

		return ok;

	}

	public synchronized void turnOffMic() {

		if (listen) {
			
			synchronized (interrupter) {
				interrupter.enable();
				while (!sleeping) {
					try {
						interrupter.wait();
					} catch (InterruptedException e) {}
				}
				microphone.stopRecording();
				microphone.clear();
			}
			
			listen = false;
		
			System.out.println("[INFO] Disabled listening to microphone");
			
		} else {

			System.out.println("[WARNING] Received 'TurnOff' request " +
					"despite not listening to microphone");
			
		}

	}

	public synchronized String setNewGrammar(String jsgfGrammar) {

		String setGrammer = null;
		
		if (jsgfGrammar != null && !jsgfGrammar.trim().isEmpty()) {
			
			// get grammar name
			String grammarName = getGrammerName(jsgfGrammar);
			if (grammarName == null) {
				System.out.println("[ERROR] Couldn't find JSGF grammar name declaration");
				return null;
			}
			
			// store grammar to file
			try {
				File grammarFile = new File(localPkgPath+relGrammarPath, 
						grammarName + ".gram");
				if (grammarFile.exists()) {
					System.out.println("[INFO] Overwriting grammar '" + 
							grammarName + ".gram'");
				}
				if (!writeFile(jsgfGrammar, grammarFile)) {
					return null;
				}
			} catch (Exception e) {
				System.out.println("[ERROR] Couldn't create grammar file '" + 
						grammarName + ".gram'");
				return null;
			}
			
			// load grammar
			if (loadGrammar(grammarName)) {
				setGrammer = grammarName;
			}
			
		}
		
		return setGrammer;

	}

	public synchronized boolean loadGrammar(String grammarName) {
		
		boolean ok = false;
		boolean restart = false;
		
		// stop recognizer if it is still running
		if (listen) {
			synchronized (interrupter) {
				interrupter.enable();
				while (!sleeping) {
					try {
						interrupter.wait();
					} catch (InterruptedException e) {}
				}
				microphone.stopRecording();
				microphone.clear();
			}
			listen = false;
			restart = true;
		}
		
		// load new grammar
		try {
			grammar.loadJSGF(grammarName);
			grammar.commitChanges();
			ok = true;
			System.out.println("[INFO] JSGF grammar '" + grammarName + "' loaded");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("[ERROR] Couldn't load grammar '" + grammarName + "'");
		}
		
		// restart recognizer if it was running before
		if (restart) {
			synchronized (interrupter) {
				while (!sleeping) {
					try {
						interrupter.wait();
					} catch (InterruptedException e) {}
				}
				
				if (microphone.startRecording()) {
					interrupter.disable();
					interrupter.notifyAll();
					listen = true;
				} else {
					System.out.println("[ERROR] Couldn't restart microphone");
				}
			}
		}
		
		return ok;
		
	}
	
	public synchronized void shutdown() {

		System.out.println();

		if (listen) {
			synchronized (interrupter) {
				interrupter.enable();
				while (!sleeping) {
					try {
						interrupter.wait();
					} catch (InterruptedException e) {}
				}
				microphone.stopRecording();
				microphone.clear();
			}
			listen = false;
		}

		shallRun = false;
		
		synchronized (interrupter) {
			interrupter.notifyAll();
		}

	}

	public void addSpeechRecListener(SpeechRecListener l) {
		listeners.add(l);	
	}

	public void removeSpeechRecListener(SpeechRecListener l) {
		listeners.remove(l);	
	}
	
	class SpeechRecognizerThread extends Thread {
		
		public SpeechRecognizerThread() {
			start();
		}
		
		@Override
		public void run() {
			
			System.out.println("\n[INFO] Startup of speech recognizer complete " +
					"(currently not listening to microphone)");

			Result result;
			while (shallRun) {

				result = null;

				try {

					result = recognizer.recognize();

				} catch (RuntimeException rte) {

					synchronized (interrupter) {
						while (interrupter.isEnabled() && shallRun) {
							sleeping = true;
							interrupter.notifyAll();
							try {
								interrupter.wait();
							} catch (InterruptedException ie) {}
							sleeping = false;
						}
					}
					
				}				

				if (result != null && result.validate()) {

					ConfidenceResult cr = scorer.score(result);
					Iterator<ConfusionSet> it = cr.iterator();
					System.out.println(" confusion set:");
					while (it.hasNext()) {
						ConfusionSet conset = it.next();
						System.out.println("  " + conset.toString());
					}
					System.out.println(" timed path:\n  " +
							result.getTimedBestResult(false, true));

					float score = 0;
					Token t = result.getBestFinalToken();
					if (t != null) {
						score = t.getScore();
						System.out.println(" pronunciation:\n  " +
								result.getBestPronunciationResult() + 
								"\n score: " + score);	
					};

					String resultText = result.getBestFinalResultNoFiller();
					System.out.println("[INFO] I heard '" + resultText + "'\n");

					synchronized (listeners) {
						for (SpeechRecListener l : listeners) {
							l.resultCallback(resultText, score);
						}
					}
					
				}

			}

			System.out.println("[INFO] Shutting down speech recognizer");
			
		}
		
	}

	public static void main(String[] args) {

		SpeechRecognizer rec = new SpeechRecognizer();
		rec.turnOnMic();

	}
	
}
