package robot_control_srvs;

public interface MoveToOSResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "robot_control_srvs/MoveToOSResponse";
  static final java.lang.String _DEFINITION = "bool success     # success of request";
  boolean getSuccess();
  void setSuccess(boolean value);
}
