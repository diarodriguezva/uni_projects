FILE(REMOVE_RECURSE
  "../srv_gen"
  "../src/dummy_robot_control/srv"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/dummy_robot_control/srv/__init__.py"
  "../src/dummy_robot_control/srv/_MoveJoints.py"
  "../src/dummy_robot_control/srv/_PrintGripperPose.py"
  "../src/dummy_robot_control/srv/_MoveToOS.py"
  "../src/dummy_robot_control/srv/_MoveToCS.py"
  "../src/dummy_robot_control/srv/_PrintPose.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
