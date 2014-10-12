package speech_recognition_srvs;

public interface AddGrammarRequest extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "speech_recognition_srvs/AddGrammarRequest";
  static final java.lang.String _DEFINITION = "string jsgfGrammar  # string containing a JSGF grammar\n";
  java.lang.String getJsgfGrammar();
  void setJsgfGrammar(java.lang.String value);
}
