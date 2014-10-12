package world_model_srvs;

public interface GetTransformRequest extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "world_model_srvs/GetTransformRequest";
  static final java.lang.String _DEFINITION = "string base_frame\nstring target_frame\n";
  java.lang.String getBaseFrame();
  void setBaseFrame(java.lang.String value);
  java.lang.String getTargetFrame();
  void setTargetFrame(java.lang.String value);
}
