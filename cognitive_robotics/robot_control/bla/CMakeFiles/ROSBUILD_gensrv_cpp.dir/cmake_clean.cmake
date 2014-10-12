FILE(REMOVE_RECURSE
  "../srv_gen"
  "../srv_gen"
  "../src/robot_control/srv"
  "CMakeFiles/ROSBUILD_gensrv_cpp"
  "../srv_gen/cpp/include/robot_control/PrintGripperPose.h"
  "../srv_gen/cpp/include/robot_control/MoveJoints.h"
  "../srv_gen/cpp/include/robot_control/MoveToOS.h"
  "../srv_gen/cpp/include/robot_control/MoveToCS.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
