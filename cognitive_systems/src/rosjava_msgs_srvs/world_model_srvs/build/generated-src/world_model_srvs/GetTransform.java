package world_model_srvs;

public interface GetTransform extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "world_model_srvs/GetTransform";
  static final java.lang.String _DEFINITION = "string base_frame\nstring target_frame\n---\ngeometry_msgs/Pose pose\nstring error_msg\nbool success\n";
}
