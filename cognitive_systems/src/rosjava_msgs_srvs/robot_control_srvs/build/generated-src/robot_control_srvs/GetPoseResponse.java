package robot_control_srvs;

public interface GetPoseResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "robot_control_srvs/GetPoseResponse";
  static final java.lang.String _DEFINITION = "bool success     # success of request\nfloat32 x\nfloat32 y\nfloat32 z";
  boolean getSuccess();
  void setSuccess(boolean value);
  float getX();
  void setX(float value);
  float getY();
  void setY(float value);
  float getZ();
  void setZ(float value);
}
