cmake_minimum_required(VERSION 2.8.3)
project(demo_cogsys_cpp_viz)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  roslib
  robot_control_srvs
  world_model_srvs
  gripper_control_srvs
  speech_recognition_msgs
  speech_recognition_srvs
  tf
)

INCLUDE(${CMAKE_ROOT}/Modules/FindQt4.cmake)
FIND_PACKAGE(OpenCV REQUIRED )
INCLUDE(${PROJECT_SOURCE_DIR}/Modules/FindEigen3.cmake)

catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES camera
 CATKIN_DEPENDS roscpp rospy roslib
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
add_executable(demo_cogsys_viz_cpp ${HDRS} ${SRCS})
add_dependencies(demo_cogsys_viz_cpp
    robot_control_srvs_generate_message_cpp
    gripper_control_srvs_generate_message_cpp
    speech_recognition_srvs_generate_message_cpp
    world_model_srvs_generate_message_cpp
    speech_recognition_msgs_generate_message_cpp
)
target_link_libraries(	demo_cogsys_viz_cpp
                        ${catkin_LIBRARIES} 
                        ${QT_QTCORE_LIBRARY}
                        ${OpenCV_LIBRARIES})

SET(HDRS_S4
        src/main.h
)

SET(SRCS_S4
        src/main_session4.cpp
)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
add_executable(demo_cogsys_viz_cpp_session4 ${HDRS_S4} ${SRCS_S4})
add_dependencies(demo_cogsys_viz_cpp_session4
    robot_control_srvs_generate_message_cpp
    gripper_control_srvs_generate_message_cpp
    speech_recognition_srvs_generate_message_cpp
    world_model_srvs_generate_message_cpp
    speech_recognition_msgs_generate_message_cpp
)
target_link_libraries(	demo_cogsys_viz_cpp_session4
                        ${catkin_LIBRARIES} 
                        ${QT_QTCORE_LIBRARY}
                        ${OpenCV_LIBRARIES})


