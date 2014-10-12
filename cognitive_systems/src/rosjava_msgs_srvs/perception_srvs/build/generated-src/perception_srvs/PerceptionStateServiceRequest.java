package perception_srvs;

public interface PerceptionStateServiceRequest extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "perception_srvs/PerceptionStateServiceRequest";
  static final java.lang.String _DEFINITION = "int32 request\n";
  int getRequest();
  void setRequest(int value);
}
