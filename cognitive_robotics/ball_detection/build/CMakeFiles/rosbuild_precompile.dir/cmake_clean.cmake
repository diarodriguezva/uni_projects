FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/ball_detection/msg"
  "../src/ball_detection/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/rosbuild_precompile"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/rosbuild_precompile.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
