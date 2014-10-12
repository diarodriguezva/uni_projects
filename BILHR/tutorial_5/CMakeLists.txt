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

find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)
find_package(OpenCV)

MESSAGE("////////////////////////////OPENCV: ${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})

#uncomment if you have defined messages
rosbuild_genmsg()

#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/filehelper.h)
#target_link_libraries(${PROJECT_NAME} another_library)
rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

#basic nodes
rosbuild_add_executable(keyboard_node src/keyboard_node.cpp )
rosbuild_add_executable(central_node  src/central_node.cpp src/Q_learner.cpp)
rosbuild_add_executable(move_leg  src/move_leg.cpp)
rosbuild_add_executable(leg_node src/leg_node.cpp)
rosbuild_add_executable(goalie_tracker src/goalie_tracker.cpp)

rosbuild_link_boost(central_node signals)
