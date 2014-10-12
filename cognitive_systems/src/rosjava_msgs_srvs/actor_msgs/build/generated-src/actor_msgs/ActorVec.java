package actor_msgs;

public interface ActorVec extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "actor_msgs/ActorVec";
  static final java.lang.String _DEFINITION = "Actor[] ActorVec\n\n\n";
  java.util.List<actor_msgs.Actor> getActorVec();
  void setActorVec(java.util.List<actor_msgs.Actor> value);
}
