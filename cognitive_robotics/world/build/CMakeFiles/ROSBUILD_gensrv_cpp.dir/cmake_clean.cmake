FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/world/msg"
  "../src/world/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_cpp"
  "../srv_gen/cpp/include/world/inspect_objects.h"
  "../srv_gen/cpp/include/world/found_objects.h"
  "../srv_gen/cpp/include/world/is_cam_moving_service.h"
  "../srv_gen/cpp/include/world/detect_objects.h"
  "../srv_gen/cpp/include/world/check_goal_position.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
