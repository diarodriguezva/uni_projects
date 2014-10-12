FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/ball_detection/msg"
  "../src/ball_detection/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/ball_detection/msg/__init__.py"
  "../src/ball_detection/msg/_Detection.py"
  "../src/ball_detection/msg/_midpoints.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
