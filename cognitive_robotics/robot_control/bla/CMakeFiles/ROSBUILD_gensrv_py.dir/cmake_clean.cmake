FILE(REMOVE_RECURSE
  "../srv_gen"
  "../srv_gen"
  "../src/robot_control/srv"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/robot_control/srv/__init__.py"
  "../src/robot_control/srv/_PrintGripperPose.py"
  "../src/robot_control/srv/_MoveJoints.py"
  "../src/robot_control/srv/_MoveToOS.py"
  "../src/robot_control/srv/_MoveToCS.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
