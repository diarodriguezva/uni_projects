package robot_control_srvs;

public interface MoveToOSRequest extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "robot_control_srvs/MoveToOSRequest";
  static final java.lang.String _DEFINITION = "string effector  # name of effector (\"wrist\" or \"gripper\" or \"camera\")\nfloat32 x        # x coordinate of position\nfloat32 y        # y coordinate of position\nfloat32 z        # z coordinate of position\n";
  java.lang.String getEffector();
  void setEffector(java.lang.String value);
  float getX();
  void setX(float value);
  float getY();
  void setY(float value);
  float getZ();
  void setZ(float value);
}
