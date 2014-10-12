package robot_control_srvs;

public interface MoveToCSResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "robot_control_srvs/MoveToCSResponse";
  static final java.lang.String _DEFINITION = "bool success     # success of request";
  boolean getSuccess();
  void setSuccess(boolean value);
}
