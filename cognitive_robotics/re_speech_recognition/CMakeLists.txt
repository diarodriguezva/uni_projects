cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#reset JSGF grammar files
file(GLOB inputs grammar/*.in)
foreach( _in ${inputs} )
  string(REPLACE ".in" "" _out ${_in})
  configure_file( ${_in} ${_out} )
endforeach( _in )

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

add_classpath(${PROJECT_SOURCE_DIR}/lib/jsapi.jar)
add_classpath(${PROJECT_SOURCE_DIR}/lib/jsapi-1.0-base.jar)
add_classpath(${PROJECT_SOURCE_DIR}/lib/sphinx4.jar)
add_classpath(${PROJECT_SOURCE_DIR}/lib/WSJ_8gau_13dCep_16k_40mel_130Hz_6800Hz.jar)
add_classpath(${PROJECT_SOURCE_DIR}/bin)

add_runtime_classpath(${PROJECT_SOURCE_DIR}/lib/jsapi.jar)
add_runtime_classpath(${PROJECT_SOURCE_DIR}/lib/jsapi-1.0-base.jar)
add_runtime_classpath(${PROJECT_SOURCE_DIR}/lib/sphinx4.jar)
add_runtime_classpath(${PROJECT_SOURCE_DIR}/lib/WSJ_8gau_13dCep_16k_40mel_130Hz_6800Hz.jar)
add_runtime_classpath(${PROJECT_SOURCE_DIR}/bin)

add_java_source_dir(${PROJECT_SOURCE_DIR}/src)
rospack_add_java_executable(test org.roboearth.wp5.speechrec.SpeechRecognizer)
rospack_add_java_executable(run org.roboearth.wp5.speechrec.ros.ROSWrapper)


