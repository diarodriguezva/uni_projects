package robot_control_srvs;

public interface GetPoseRequest extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "robot_control_srvs/GetPoseRequest";
  static final java.lang.String _DEFINITION = "string effector  # name of effector (\"wrist\" or \"gripper\" or \"camera\")\n";
  java.lang.String getEffector();
  void setEffector(java.lang.String value);
}
