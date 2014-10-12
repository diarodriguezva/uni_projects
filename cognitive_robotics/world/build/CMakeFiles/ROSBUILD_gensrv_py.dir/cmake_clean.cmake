FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/world/msg"
  "../src/world/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/world/srv/__init__.py"
  "../src/world/srv/_inspect_objects.py"
  "../src/world/srv/_found_objects.py"
  "../src/world/srv/_is_cam_moving_service.py"
  "../src/world/srv/_detect_objects.py"
  "../src/world/srv/_check_goal_position.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
