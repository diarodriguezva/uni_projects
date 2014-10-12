package actor_msgs;

public interface Actor extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "actor_msgs/Actor";
  static final java.lang.String _DEFINITION = "geometry_msgs/Pose[] targetPoseVec\n\nstring targetType\nint32 actorType #ASSEMBLY, WELDING\nstring associatedActor\n\nstring targetProperty\n\nstring description\n\nstring timeStamp\n\t\nstring semanticName\n\nint32 targetId\n\nstring modelPath\n\nbool isRobot\nstring kinematicModelPath\n\n#welding parameters\nfloat32 weldingCurrent\nfloat32 weldingVoltage\nfloat32 robotMovingSpeed\nfloat32 spotWeldingTime\n\n \n\n";
  java.util.List<geometry_msgs.Pose> getTargetPoseVec();
  void setTargetPoseVec(java.util.List<geometry_msgs.Pose> value);
  java.lang.String getTargetType();
  void setTargetType(java.lang.String value);
  int getActorType();
  void setActorType(int value);
  java.lang.String getAssociatedActor();
  void setAssociatedActor(java.lang.String value);
  java.lang.String getTargetProperty();
  void setTargetProperty(java.lang.String value);
  java.lang.String getDescription();
  void setDescription(java.lang.String value);
  java.lang.String getTimeStamp();
  void setTimeStamp(java.lang.String value);
  java.lang.String getSemanticName();
  void setSemanticName(java.lang.String value);
  int getTargetId();
  void setTargetId(int value);
  java.lang.String getModelPath();
  void setModelPath(java.lang.String value);
  boolean getIsRobot();
  void setIsRobot(boolean value);
  java.lang.String getKinematicModelPath();
  void setKinematicModelPath(java.lang.String value);
  float getWeldingCurrent();
  void setWeldingCurrent(float value);
  float getWeldingVoltage();
  void setWeldingVoltage(float value);
  float getRobotMovingSpeed();
  void setRobotMovingSpeed(float value);
  float getSpotWeldingTime();
  void setSpotWeldingTime(float value);
}
