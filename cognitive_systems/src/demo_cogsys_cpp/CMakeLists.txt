cmake_minimum_required(VERSION 2.8.3)
project(demo_cogsys_cpp)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  roslib
  camera_srvs
  comm_lib
  robot_control
  gripper_control
  object_detector
  perception_msgs
  perception_srvs
  robot_control_srvs
  gripper_control_srvs
  speech_recognition_msgs
  speech_recognition_srvs
)

INCLUDE(${CMAKE_ROOT}/Modules/FindQt4.cmake)
FIND_PACKAGE(OpenCV REQUIRED )
INCLUDE(${PROJECT_SOURCE_DIR}/Modules/FindEigen3.cmake)

catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES camera
 CATKIN_DEPENDS roscpp rospy roslib comm_lib robot_control gripper_control object_detector
#  DEPENDS system_lib
)

INCLUDE_DIRECTORIES(
  ${catkin_INCLUDE_DIRS}
        ${QT_INCLUDES}
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${OPENCV_INCLUDES}
        ${EIGEN3_INCLUDE_DIR}
        /usr/include
        /usr/local/include
)

LINK_DIRECTORIES(
        /usr/local/lib
        /usr/lib
)

SET(HDRS
        src/main.h
)

SET(SRCS
        src/main.cpp
)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
add_executable(demo_cogsys_cpp ${HDRS} ${SRCS})
target_link_libraries(	demo_cogsys_cpp
                        ${catkin_LIBRARIES} 
                        ${QT_QTCORE_LIBRARY}
                        ${OpenCV_LIBRARIES})


