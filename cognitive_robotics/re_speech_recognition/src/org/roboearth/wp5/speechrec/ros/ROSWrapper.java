package org.roboearth.wp5.speechrec.ros;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

import org.roboearth.wp5.speechrec.SpeechRecListener;
import org.roboearth.wp5.speechrec.SpeechRecognizer;

import ros.NodeHandle;
import ros.Publisher;
import ros.Ros;
import ros.RosException;
import ros.ServiceServer;
import ros.pkg.re_speech_recognition.msg.RecognizedSpeech;
import ros.pkg.re_speech_recognition.srv.LoadGrammar;
import ros.pkg.re_speech_recognition.srv.SetNewGrammar;
import ros.pkg.re_speech_recognition.srv.TurnOff;
import ros.pkg.re_speech_recognition.srv.TurnOn;


public class ROSWrapper implements SpeechRecListener {

	protected SpeechRecognizer rec;
	protected Ros ros;
	protected NodeHandle n;
	protected Publisher<RecognizedSpeech> pubResult;
	
	public ROSWrapper(Ros ros, NodeHandle n) throws RosException {
		
		this.ros = ros;
		this.n = n;
		rec = new SpeechRecognizer();
		rec.addSpeechRecListener(this);

		pubResult = n.advertise("/re_speech_recognition/output", new RecognizedSpeech(), 100);
		
		n.advertiseService("/re_speech_recognition/turn_on", new TurnOn(), new TurnOnCallback());
		n.advertiseService("/re_speech_recognition/turn_off", new TurnOff(), new TurnOffCallback());
		n.advertiseService("/re_speech_recognition/set_new_grammar", new SetNewGrammar(), new SetNewGrammarCallback());
		n.advertiseService("/re_speech_recognition/load_grammar", new LoadGrammar(), new LoadGrammarCallback());
		
	}
	
	public void shutdown() {
		
		rec.shutdown();
		
	}

	@Override
	public void resultCallback(String text, float score) {

		RecognizedSpeech s = new RecognizedSpeech();
		s.speech = text;
		s.score = score;
		pubResult.publish(s);
		
	}
	
	public static String getLocalPackagePath(String packageName) {

		String dir = null;

		try {	

			// try to find package using rospack
			String line;
			Process get_path = new ProcessBuilder( "rospack", "find", packageName).start();

			try {
				BufferedReader pathreader = new BufferedReader(new InputStreamReader(get_path.getInputStream(), "UTF-8"));

				if( (line = pathreader.readLine()) != null) {
					dir = line+File.separator;
				}
			} finally {
				if (get_path != null) {
					get_path.getInputStream().close();	
				}
			}

		} catch (IOException e) {
			e.printStackTrace(System.err);
		}

		return dir;

	}
	
	class TurnOnCallback implements ServiceServer.Callback<TurnOn.Request, TurnOn.Response> {

		@Override
		public TurnOn.Response call(TurnOn.Request req) {
			
			TurnOn.Response res = new TurnOn.Response();
			res.success = rec.turnOnMic(); 
			return res;

		}

	}

	class TurnOffCallback implements ServiceServer.Callback<TurnOff.Request, TurnOff.Response> {

		@Override
		public TurnOff.Response call(TurnOff.Request req) {

			TurnOff.Response res = new TurnOff.Response();
			rec.turnOffMic();
			return res;

		}

	}
	
	class SetNewGrammarCallback implements ServiceServer.Callback<SetNewGrammar.Request, SetNewGrammar.Response> {

		@Override
		public SetNewGrammar.Response call(SetNewGrammar.Request req) {
			
			SetNewGrammar.Response res = new SetNewGrammar.Response();
			
			String grammarName = rec.setNewGrammar(req.jsgfGrammar);
			res.success = (grammarName != null);
			if (res.success) {
				res.name = grammarName;
			}
			return res;

		}

	}
	
	class LoadGrammarCallback implements ServiceServer.Callback<LoadGrammar.Request, LoadGrammar.Response> {

		@Override
		public LoadGrammar.Response call(LoadGrammar.Request req) {
			
			LoadGrammar.Response res = new LoadGrammar.Response();
			res.success = rec.loadGrammar(req.name);
			return res;

		}

	}
	
	/**
	 * The main method initializes rosjava and creates a ROS node providing
	 * functionalities based on the loaded modules.  
	 */
	public static void main(String[] args) {

		// Initialize rosjava 
		Ros ros = Ros.getInstance();
		ros.init("re_speech_recognition");

		// Create a NodeHandle
		NodeHandle n = ros.createNodeHandle();
		
		ROSWrapper w = null;
		try {
			
			w = new ROSWrapper(ros, n);
			
		} catch (Exception e) {
			ros.logFatal("Fatal error occurred. Shutting down!");	
			
			if (n != null) {
				n.shutdown();	
			}
			
			e.printStackTrace();
			return;
		}

		ros.spin();
		
		w.shutdown();
		
	}

}
