package world_model_srvs;

public interface GetTransformResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "world_model_srvs/GetTransformResponse";
  static final java.lang.String _DEFINITION = "geometry_msgs/Pose pose\nstring error_msg\nbool success";
  geometry_msgs.Pose getPose();
  void setPose(geometry_msgs.Pose value);
  java.lang.String getErrorMsg();
  void setErrorMsg(java.lang.String value);
  boolean getSuccess();
  void setSuccess(boolean value);
}
