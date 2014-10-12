cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

IF(WIN32) # platform defines for Windows 32bit Systems
        # define math constants like M_PI on Windows
        ADD_DEFINITIONS(-D_USE_MATH_DEFINES)
        # use the winGSL library
        ADD_DEFINITIONS(-DGSL_DLL)

ELSEIF(APPLE) # platform defines for Mac OS X Systems
        IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
                ADD_DEFINITIONS(-DPOSIX -DAPPLE)
        ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

ELSE(WIN32)	# assumes linux/UNIX # platform defines for Linux Systems
        ADD_DEFINITIONS(-DPOSIX -DLINUX -D__LINUX__)
ENDIF(WIN32)

# add global definitions (all platforms, all compilers, all sources)
ADD_DEFINITIONS(-DNOMINMAX)

IF (CMAKE_BUILD_TYPE)
        STRING(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
        STRING(COMPARE EQUAL ${BUILD_TYPE} "debug" DEBUG)
        STRING(COMPARE EQUAL ${BUILD_TYPE} "relwithdebinfo" RELWITHDEBINFO)
        IF (DEBUG OR RELWITHDEBINFO)
                ADD_DEFINITIONS(-DDEBUG)
        ENDIF (DEBUG OR RELWITHDEBINFO)
ENDIF (CMAKE_BUILD_TYPE)

INCLUDE(${CMAKE_ROOT}/Modules/FindQt4.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/Modules/FindEigen3.cmake)

#-- Add an Option to toggle the generation of the API documentation
option(BUILD_DOCUMENTATION "Use Doxygen to create the HTML based API documentation" OFF)
if(BUILD_DOCUMENTATION)
  FIND_PACKAGE(Doxygen)
  if (NOT DOXYGEN_FOUND)
    message(FATAL_ERROR
      "Doxygen is needed to build the documentation. Please install it correctly")
  endif()
  #-- Configure the Template Doxyfile for our specific project
  configure_file(Doxyfile.in
                 ${PROJECT_BINARY_DIR}/Doxyfile  @ONLY IMMEDIATE)
  #-- Add a custom target to run Doxygen when ever the project is built
  add_custom_target (Docs ALL
 COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
 SOURCES ${PROJECT_BINARY_DIR}/Doxyfile)
  # IF you do NOT want the documentation to be generated EVERY time you build the project
  # then leave out the 'ALL' keyword from the above command.
endif()


INCLUDE_DIRECTORIES(
        ${QT_INCLUDES}
        ${EIGEN3_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/ros_comm_lib
        ${PROJECT_SOURCE_DIR}/include/ros_comm_lib/util
	${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/util
        /usr/include
        /usr/local/include
)

LINK_DIRECTORIES(
        /usr/local/lib
        /usr/lib
)

SET(HDRS
	include/ros_comm_lib/CommonDefs.h
        include/ros_comm_lib/RosActorsPublisher.h
        include/ros_comm_lib/RosImagePublisher.h
        include/ros_comm_lib/RosActionPublisher.h
        include/ros_comm_lib/RosTaskStatusPublisher.h
        #include/ros_comm_lib/RosRobotStatusPublisher.h
        include/ros_comm_lib/RosDeviceStatusPublisher.h
        #include/ros_comm_lib/RosGripperStatusPublisher.h
        include/ros_comm_lib/RosActorsSubscriber.h
        include/ros_comm_lib/RosImageSubscriber.h
        include/ros_comm_lib/RosActionSubscriber.h
        include/ros_comm_lib/RosTaskStatusSubscriber.h
        #include/ros_comm_lib/RosRobotStatusSubscriber.h
        #include/ros_comm_lib/RosGripperStatusSubscriber.h
        include/ros_comm_lib/RosDeviceStatusSubscriber.h
        include/ros_comm_lib/util/Util.h
)

SET(SRCS

        src/RosActorsPublisher.cpp
        src/RosImageSubscriber.cpp
        src/RosImagePublisher.cpp
        src/RosActionPublisher.cpp
        src/RosTaskStatusPublisher.cpp
        #src/RosRobotStatusPublisher.cpp
        src/RosDeviceStatusPublisher.cpp
        #src/RosGripperStatusPublisher.cpp
        src/RosActorsSubscriber.cpp
        src/RosActionSubscriber.cpp
        src/RosTaskStatusSubscriber.cpp
        #src/RosRobotStatusSubscriber.cpp
        #src/RosGripperStatusSubscriber.cpp
        src/RosDeviceStatusSubscriber.cpp
        src/util/Util.cpp
)


#common commands for building c++ executables and libraries
rosbuild_add_library(ros_comm ${HDRS} ${SRCS})
target_link_libraries(ros_comm ${QT_QTCORE_LIBRARY})

#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})
