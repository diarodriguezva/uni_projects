package device_msgs;

public interface CameraCalibData extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "device_msgs/CameraCalibData";
  static final java.lang.String _DEFINITION = "int32 width\nint32 height\nstring encoding\nfloat64[9] K\nfloat64[16] E\nfloat64[12] P\n";
  int getWidth();
  void setWidth(int value);
  int getHeight();
  void setHeight(int value);
  java.lang.String getEncoding();
  void setEncoding(java.lang.String value);
  double[] getK();
  void setK(double[] value);
  double[] getE();
  void setE(double[] value);
  double[] getP();
  void setP(double[] value);
}
