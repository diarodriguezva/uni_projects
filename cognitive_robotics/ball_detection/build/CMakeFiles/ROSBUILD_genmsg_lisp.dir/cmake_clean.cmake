FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/ball_detection/msg"
  "../src/ball_detection/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/Detection.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_Detection.lisp"
  "../msg_gen/lisp/midpoints.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_midpoints.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
