package robot_control_srvs;

public interface MoveToOS extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "robot_control_srvs/MoveToOS";
  static final java.lang.String _DEFINITION = "string effector  # name of effector (\"wrist\" or \"gripper\" or \"camera\")\nfloat32 x        # x coordinate of position\nfloat32 y        # y coordinate of position\nfloat32 z        # z coordinate of position\n---\nbool success     # success of request\n\n";
}
