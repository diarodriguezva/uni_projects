package device_msgs;

public interface Mode extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "device_msgs/Mode";
  static final java.lang.String _DEFINITION = "#DeviceMode {DISABLED, STATIONARY, MOVING, OPEN, CLOSE}\n\nint32 DISABLED \t = 0\nint32 STATIONARY = 1\nint32 MOVING \t = 2\nint32 OPEN\t = 3\nint32 CLOSE\t = 4\n\nint32 GRASPING_STATE_IDLE = 1001\nint32 GRASPING_STATE_GRASPING = 1002\nint32 GRASPING_STATE_NO_PART_FOUND = 1003\nint32 GRASPING_STATE_PART_LOST = 1004\nint32 GRASPING_STATE_HOLDING = 1005\nint32 GRASPING_STATE_RELEASING = 1006\nint32 GRASPING_STATE_POSITIONING = 1007\nint32 GRASPING_STATE_ERROR = 1008\n";
  static final int DISABLED = 0;
  static final int STATIONARY = 1;
  static final int MOVING = 2;
  static final int OPEN = 3;
  static final int CLOSE = 4;
  static final int GRASPING_STATE_IDLE = 1001;
  static final int GRASPING_STATE_GRASPING = 1002;
  static final int GRASPING_STATE_NO_PART_FOUND = 1003;
  static final int GRASPING_STATE_PART_LOST = 1004;
  static final int GRASPING_STATE_HOLDING = 1005;
  static final int GRASPING_STATE_RELEASING = 1006;
  static final int GRASPING_STATE_POSITIONING = 1007;
  static final int GRASPING_STATE_ERROR = 1008;
}
