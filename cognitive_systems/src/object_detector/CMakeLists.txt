cmake_minimum_required(VERSION 2.8.3)
project(object_detector)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  roslib
  camera_srvs
  comm_lib
  perception_msgs
  perception_srvs
  robot_control_srvs
  gripper_control_srvs
)

INCLUDE(${CMAKE_ROOT}/Modules/FindQt4.cmake)
FIND_PACKAGE(OpenCV REQUIRED )
INCLUDE(${PROJECT_SOURCE_DIR}/Modules/FindEigen3.cmake)


catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES camera
 CATKIN_DEPENDS roscpp rospy roslib comm_lib
#  DEPENDS system_lib
)


INCLUDE_DIRECTORIES(
        ${QT_INCLUDES}
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${OPENCV_INCLUDES}
        ${EIGEN3_INCLUDE_DIR}
        include
        ${catkin_INCLUDE_DIRS}
        /usr/include
        /usr/local/include
)

LINK_DIRECTORIES(
        /usr/local/lib
        /usr/lib
)


SET(HDRS
        src/detector/Detector.h
        src/detector/DetectorThread.h
        src/main.h
)

SET(SRCS
        src/detector/Detector.cpp
        src/detector/DetectorThread.cpp
        src/main.cpp
)


#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
add_executable(objdetect ${HDRS} ${SRCS})
target_link_libraries(	objdetect
        ${catkin_LIBRARIES}            
	${QT_QTCORE_LIBRARY}
        ${OpenCV_LIBRARIES}
)


