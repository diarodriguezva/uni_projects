FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/ball_detection/msg"
  "../src/ball_detection/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_lisp"
  "../srv_gen/lisp/find_balls.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_find_balls.lisp"
  "../srv_gen/lisp/find_boxes.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_find_boxes.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
