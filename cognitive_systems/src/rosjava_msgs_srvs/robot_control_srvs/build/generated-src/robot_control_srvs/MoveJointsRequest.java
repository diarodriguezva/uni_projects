package robot_control_srvs;

public interface MoveJointsRequest extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "robot_control_srvs/MoveJointsRequest";
  static final java.lang.String _DEFINITION = "float32 q0       # joint0\nfloat32 q1       # joint1\nfloat32 q2       # joint2\n";
  float getQ0();
  void setQ0(float value);
  float getQ1();
  void setQ1(float value);
  float getQ2();
  void setQ2(float value);
}
