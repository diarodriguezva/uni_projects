package action_msgs;

public interface Action extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "action_msgs/Action";
  static final java.lang.String _DEFINITION = "#Action Structure\n\nint32 name\n\nactor_msgs/Actor actor\n\nstring uniqueIdentifier\n";
  int getName();
  void setName(int value);
  actor_msgs.Actor getActor();
  void setActor(actor_msgs.Actor value);
  java.lang.String getUniqueIdentifier();
  void setUniqueIdentifier(java.lang.String value);
}
