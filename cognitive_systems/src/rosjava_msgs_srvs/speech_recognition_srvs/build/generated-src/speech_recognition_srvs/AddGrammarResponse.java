package speech_recognition_srvs;

public interface AddGrammarResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "speech_recognition_srvs/AddGrammarResponse";
  static final java.lang.String _DEFINITION = "bool success        # success of request\nstring name         # name that was given to grammar";
  boolean getSuccess();
  void setSuccess(boolean value);
  java.lang.String getName();
  void setName(java.lang.String value);
}
