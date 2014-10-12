package device_msgs;

public interface Status extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "device_msgs/Status";
  static final java.lang.String _DEFINITION = "string deviceName\n\nint32 mode\n\nint32 action\n\nstring actionIdentifier\n\nint32 result\n\t\nstring timeStamp\n";
  java.lang.String getDeviceName();
  void setDeviceName(java.lang.String value);
  int getMode();
  void setMode(int value);
  int getAction();
  void setAction(int value);
  java.lang.String getActionIdentifier();
  void setActionIdentifier(java.lang.String value);
  int getResult();
  void setResult(int value);
  java.lang.String getTimeStamp();
  void setTimeStamp(java.lang.String value);
}
