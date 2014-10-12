FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/world/msg"
  "../src/world/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_lisp"
  "../srv_gen/lisp/inspect_objects.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_inspect_objects.lisp"
  "../srv_gen/lisp/found_objects.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_found_objects.lisp"
  "../srv_gen/lisp/is_cam_moving_service.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_is_cam_moving_service.lisp"
  "../srv_gen/lisp/detect_objects.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_detect_objects.lisp"
  "../srv_gen/lisp/check_goal_position.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_check_goal_position.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
