FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/ball_detection/msg"
  "../src/ball_detection/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/ball_detection/srv/__init__.py"
  "../src/ball_detection/srv/_find_balls.py"
  "../src/ball_detection/srv/_find_boxes.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
