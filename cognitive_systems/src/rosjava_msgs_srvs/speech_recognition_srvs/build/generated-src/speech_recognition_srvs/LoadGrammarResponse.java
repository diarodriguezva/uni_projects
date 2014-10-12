package speech_recognition_srvs;

public interface LoadGrammarResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "speech_recognition_srvs/LoadGrammarResponse";
  static final java.lang.String _DEFINITION = "bool success   # success of request";
  boolean getSuccess();
  void setSuccess(boolean value);
}
