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

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

add_classpath(${PROJECT_SOURCE_DIR}/lib/cmulex.jar)
add_classpath(${PROJECT_SOURCE_DIR}/lib/cmu_us_kal.jar)
add_classpath(${PROJECT_SOURCE_DIR}/lib/en_us.jar)
add_classpath(${PROJECT_SOURCE_DIR}/lib/freetts.jar)
add_classpath(${PROJECT_SOURCE_DIR}/bin)

add_runtime_classpath(${PROJECT_SOURCE_DIR}/lib/cmulex.jar)
add_runtime_classpath(${PROJECT_SOURCE_DIR}/lib/cmu_us_kal.jar)
add_runtime_classpath(${PROJECT_SOURCE_DIR}/lib/en_us.jar)
add_runtime_classpath(${PROJECT_SOURCE_DIR}/lib/freetts.jar)
add_runtime_classpath(${PROJECT_SOURCE_DIR}/bin)

add_java_source_dir(${PROJECT_SOURCE_DIR}/src)
rospack_add_java_executable(run org.roboearth.wp5.tts.TTS)
