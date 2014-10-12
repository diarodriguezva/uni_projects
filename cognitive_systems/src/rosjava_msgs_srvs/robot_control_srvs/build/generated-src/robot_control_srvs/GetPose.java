package robot_control_srvs;

public interface GetPose extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "robot_control_srvs/GetPose";
  static final java.lang.String _DEFINITION = "string effector  # name of effector (\"wrist\" or \"gripper\" or \"camera\")\n---\nbool success     # success of request\nfloat32 x\nfloat32 y\nfloat32 z\n";
}
