package robot_control_srvs;

public interface MoveJoints extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "robot_control_srvs/MoveJoints";
  static final java.lang.String _DEFINITION = "float32 q0       # joint0\nfloat32 q1       # joint1\nfloat32 q2       # joint2\n---\nbool success     # success of request\n\n";
}
