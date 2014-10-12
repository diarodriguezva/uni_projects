FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/robot_control/msg"
  "../src/robot_control/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/rospack_gensrv"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/rospack_gensrv.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
