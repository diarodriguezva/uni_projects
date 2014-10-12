package camera_srvs;

public interface CameraInfoResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "camera_srvs/CameraInfoResponse";
  static final java.lang.String _DEFINITION = "device_msgs/CameraCalibData response";
  device_msgs.CameraCalibData getResponse();
  void setResponse(device_msgs.CameraCalibData value);
}
