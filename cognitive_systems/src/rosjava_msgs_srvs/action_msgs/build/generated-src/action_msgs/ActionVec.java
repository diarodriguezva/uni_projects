package action_msgs;

public interface ActionVec extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "action_msgs/ActionVec";
  static final java.lang.String _DEFINITION = "#Action Vector\n\nAction[] ActionVec\n";
  java.util.List<action_msgs.Action> getActionVec();
  void setActionVec(java.util.List<action_msgs.Action> value);
}
