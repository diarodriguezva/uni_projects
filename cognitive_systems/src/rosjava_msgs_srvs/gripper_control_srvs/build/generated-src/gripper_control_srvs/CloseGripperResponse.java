package gripper_control_srvs;

public interface CloseGripperResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "gripper_control_srvs/CloseGripperResponse";
  static final java.lang.String _DEFINITION = "bool success  # success of request";
  boolean getSuccess();
  void setSuccess(boolean value);
}
