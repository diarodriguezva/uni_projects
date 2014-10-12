FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/robot_control/msg"
  "../src/robot_control/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_cpp"
  "../srv_gen/cpp/include/robot_control/MoveJoints.h"
  "../srv_gen/cpp/include/robot_control/PrintGripperPose.h"
  "../srv_gen/cpp/include/robot_control/MoveToOS.h"
  "../srv_gen/cpp/include/robot_control/MoveToCS.h"
  "../srv_gen/cpp/include/robot_control/PrintPose.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
