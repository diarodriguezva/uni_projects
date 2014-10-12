FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/ball_detection/msg"
  "../src/ball_detection/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_cpp"
  "../srv_gen/cpp/include/ball_detection/find_balls.h"
  "../srv_gen/cpp/include/ball_detection/find_boxes.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
