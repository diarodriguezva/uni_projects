package speech_recognition_srvs;

public interface LoadGrammar extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "speech_recognition_srvs/LoadGrammar";
  static final java.lang.String _DEFINITION = "string name    # name of JSGF grammar to load (must have been manually stored \n               # to speech_recognition/grammar/ or sent there using the \n               # SetNewGrammar service)\n---\nbool success   # success of request\n";
}
