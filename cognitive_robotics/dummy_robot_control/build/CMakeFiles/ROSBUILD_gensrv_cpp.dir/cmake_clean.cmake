FILE(REMOVE_RECURSE
  "../srv_gen"
  "../src/dummy_robot_control/srv"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_cpp"
  "../srv_gen/cpp/include/dummy_robot_control/MoveJoints.h"
  "../srv_gen/cpp/include/dummy_robot_control/PrintGripperPose.h"
  "../srv_gen/cpp/include/dummy_robot_control/MoveToOS.h"
  "../srv_gen/cpp/include/dummy_robot_control/MoveToCS.h"
  "../srv_gen/cpp/include/dummy_robot_control/PrintPose.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
