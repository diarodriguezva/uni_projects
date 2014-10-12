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
#rosbuild_gensrv()

INCLUDE(${CMAKE_ROOT}/Modules/FindQt4.cmake)
FIND_PACKAGE(OpenCV REQUIRED )
INCLUDE(${PROJECT_SOURCE_DIR}/Modules/FindEigen3.cmake)

INCLUDE_DIRECTORIES(
        ${QT_INCLUDES}
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${OpenCV_INCLUDES}
        ${EIGEN3_INCLUDE_DIR}
        /usr/include
        /usr/local/include
)

LINK_DIRECTORIES(
        /usr/local/lib
        /usr/lib
)

SET(HDRS
        src/camInput/Cam.h
        src/camInput/CamOpenCV.h
        src/ConfigData.h          
        src/main.h
)

SET(SRCS
        src/camInput/Cam.cpp
        src/camInput/CamOpenCV.cpp
        src/ConfigData.cpp
        src/main.cpp
)
rosbuild_add_executable(camera ${HDRS} ${SRCS})
target_link_libraries(	camera
                        ${QT_QTCORE_LIBRARY}
                        ${OpenCV_LIBRARIES})

