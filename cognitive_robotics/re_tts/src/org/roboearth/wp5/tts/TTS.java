package org.roboearth.wp5.tts;

import ros.NodeHandle;
import ros.Publisher;
import ros.Ros;
import ros.RosException;
import ros.ServiceServer;
import ros.communication.Time;
import ros.pkg.re_tts.srv.Talk;

import com.sun.speech.freetts.Voice;
import com.sun.speech.freetts.VoiceManager;

public class TTS {

	protected Ros ros;
	protected NodeHandle n;

	protected static String voiceName = "kevin16";
	protected static Voice voice;
	
	protected static float stdVolume = 1f;
	protected static float stdRate = 150f;

	protected Publisher<ros.pkg.std_msgs.msg.String> pub;
	
	public TTS(Ros ros, NodeHandle n) throws RosException {

		this.ros = ros;
		this.n = n;

		this.n.advertiseService("/re_tts/talk", new Talk(), new TalkCallback());
		this.pub = n.advertise("/re_tts/status", new ros.pkg.std_msgs.msg.String(), 100);
		
	}

	/**
	 * 
	 * The callback class for the /re_tts/talk ROS service.
	 * 
	 * @author Alexander Perzylo, perzylo@cs.tum.edu
	 * 
	 */
	class TalkCallback implements ServiceServer.Callback<Talk.Request, Talk.Response> {

		@Override
		public Talk.Response call(Talk.Request req) {

			Talk.Response res = new Talk.Response();
			res.success = false;

			float vol = req.vol > 0f && req.vol < 1f ? req.vol : stdVolume;
			float rate = req.rate >= 9f && req.rate <= 999f ? req.rate : stdRate;
			
			voice.setVolume(vol);
			voice.setRate(rate);
			
			String s = req.text.trim();
			res.time = Time.now();
			if (voice.speak(s)) {
				res.dur = Time.now().subtract(res.time);
				res.success = true;
				
				// publish message about last statement
				ros.pkg.std_msgs.msg.String m = new ros.pkg.std_msgs.msg.String();
				m.data = s;
				pub.publish(m);
			}

			if (res.success) {
				ros.logInfo("Successfully said '" + s + "' (vol:"+vol+", rate:"+rate+" wpm)");
			} else {
				ros.logInfo("Saying '" + s + "' failed (vol:"+vol+", rate:"+rate+" wpm)");
			}

			return res;

		}

	}

	protected static void speakAsync(final String s) {

		Runnable r = new Runnable() {

			@Override
			public void run() {
				voice.speak(s);
			}

		};

		new Thread(r).start();

	}

	public static void main(String[] args) {

		System.setProperty("com.sun.speech.freetts.voice.defaultAudioPlayer",
				"org.roboearth.wp5.tts.REStreamingAudioPlayer");

		// Search for Voice
		VoiceManager voiceManager = VoiceManager.getInstance();
		voice = voiceManager.getVoice(voiceName);

		if (voice == null) {
			System.out.println("Couldn't find voice: " + voiceName);
			return;
		}
		voice.setDetailedMetrics(true);
		voice.allocate();

		// Initialize rosjava
		Ros ros = Ros.getInstance();
		ros.init("re_tts");

		// Create a NodeHandle
		NodeHandle n = ros.createNodeHandle();

		// Start TTS server
		try {

			new TTS(ros, n);

		} catch (Exception e) {

			ros.logFatal("Fatal error occurred. Shutting down!");
			
			if (n != null) {
				n.shutdown();
			}

			e.printStackTrace();
			return;

		}

		ros.logInfo("Waiting for service calls.");
		TTS.speakAsync("I am ready");
		ros.spin();

		voice.deallocate();

	}

}
