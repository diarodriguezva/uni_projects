package speech_recognition_msgs;

public interface RecognizedSpeech extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "speech_recognition_msgs/RecognizedSpeech";
  static final java.lang.String _DEFINITION = "string speech  # recognized speech as a string\nfloat32 score  # confidence score \n";
  java.lang.String getSpeech();
  void setSpeech(java.lang.String value);
  float getScore();
  void setScore(float value);
}
