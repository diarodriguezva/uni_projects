FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/robot_control/msg"
  "../src/robot_control/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/robot_control/msg/__init__.py"
  "../src/robot_control/msg/_pose.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
