FILE(REMOVE_RECURSE
  "../srv_gen"
  "../srv_gen"
  "../src/robot_control/srv"
  "CMakeFiles/ROSBUILD_gensrv_lisp"
  "../srv_gen/lisp/PrintGripperPose.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_PrintGripperPose.lisp"
  "../srv_gen/lisp/MoveJoints.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_MoveJoints.lisp"
  "../srv_gen/lisp/MoveToOS.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_MoveToOS.lisp"
  "../srv_gen/lisp/MoveToCS.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_MoveToCS.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
