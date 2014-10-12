package perception_srvs;

public interface PerceptionStateServiceResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "perception_srvs/PerceptionStateServiceResponse";
  static final java.lang.String _DEFINITION = "int32 response";
  int getResponse();
  void setResponse(int value);
}
