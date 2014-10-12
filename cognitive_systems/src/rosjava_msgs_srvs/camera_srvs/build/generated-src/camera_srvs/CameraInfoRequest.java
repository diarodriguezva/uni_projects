package camera_srvs;

public interface CameraInfoRequest extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "camera_srvs/CameraInfoRequest";
  static final java.lang.String _DEFINITION = "int32 request\n";
  int getRequest();
  void setRequest(int value);
}
