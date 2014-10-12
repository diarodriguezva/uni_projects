cmake_minimum_required(VERSION 2.8.3)
project(cogsys_visualization)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules)

find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Coin REQUIRED)
find_package(SoQt REQUIRED)
find_package(Eigen REQUIRED)
find_package(LibXml2 REQUIRED)
# find_package(RL COMPONENTS UTIL REQUIRED)
find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork QtOpenGL)
find_package(Bullet REQUIRED)
find_package(Ode)
find_package(Pqp)
find_package(Solid)

include(${QT_USE_FILE})

#ADD_DEFINITIONS(
#  ${RL_DEFINITIONS}
#)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependencies might have been
##     pulled in transitively but can be declared for certainty nonetheless:
##     * add a build_depend tag for "message_generation"
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES cogsys_visualization
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${QT_INCLUDES}
  ${Boost_INCLUDE_DIR}
  ${EIGEN_INCLUDE_DIRS}
  ${LIBXML2_INCLUDE_DIR}
#  ${RL_INCLUDE_DIRS}
  ${COIN_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${SOQT_INCLUDE_DIRS}
  src/rl/math
  src/rl/mdl
  src/rl/sg
  src/rl/util
  src/rl/xml
  /usr/include/libxml2/
  ${BULLET_INCLUDE_DIRS}
  ${ODE_INCLUDE_DIRS}
  #${PQP_INCLUDE_DIRS}
  ${SOLID_INCLUDE_DIRS}
)


set(
  HDRS
  src/ConfigurationDelegate.h
  src/ConfigurationModel.h
  src/MainWindow.h
  src/OperationalDelegate.h
  src/OperationalModel.h
  src/Server.h
  src/Socket.h
  src/SoGradientBackground.h
)

set(
  SRCS
  src/ConfigurationDelegate.cpp
  src/ConfigurationModel.cpp
  src/MainWindow.cpp
  src/OperationalDelegate.cpp
  src/OperationalModel.cpp
  src/rlCoachMdl.cpp
  src/Server.cpp
  src/Socket.cpp
  src/SoGradientBackground.cpp
)

qt4_wrap_cpp(
  MOC_SRCS
  src/ConfigurationDelegate.h
  src/ConfigurationModel.h
  src/MainWindow.h
  src/OperationalDelegate.h
  src/OperationalModel.h
  src/Server.h
  src/Socket.h
  OPTIONS
  -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED
)


## Declare a cpp library
add_library(cogsys_rlmath
  src/rl/math/ArticulatedBodyInertia.h
  src/rl/math/ArticulatedBodyInertia.hxx
  src/rl/math/ForceVector.h
  src/rl/math/ForceVector.hxx
  src/rl/math/Kalman.h
  src/rl/math/Matrix.h
  src/rl/math/MatrixBaseAddons.h
  src/rl/math/MotionVector.h
  src/rl/math/MotionVector.hxx
  src/rl/math/Pid.h
  src/rl/math/PlueckerTransform.h
  src/rl/math/PlueckerTransform.hxx
  src/rl/math/Quaternion.h
  src/rl/math/QuaternionBaseAddons.h
  src/rl/math/Real.h
  src/rl/math/RigidBodyInertia.h
  src/rl/math/RigidBodyInertia.hxx
  src/rl/math/Rotation.h
  src/rl/math/Spatial.h
  src/rl/math/Transform.h
  src/rl/math/TransformAddons.h
  src/rl/math/TrapezoidalVelocity.h
  src/rl/math/Unit.h
  src/rl/math/Vector.h
  src/rl/math/dummy.cpp
)


add_library(cogsys_rlxml
  src/rl/xml/Attribute.h
  src/rl/xml/Document.h
  src/rl/xml/DomParser.h
  src/rl/xml/Exception.h
  src/rl/xml/Node.h
  src/rl/xml/Namespace.h
  src/rl/xml/Object.h
  src/rl/xml/Path.h
  src/rl/xml/Schema.h
  src/rl/xml/dummy.cpp
)

target_link_libraries(
  cogsys_rlxml
  ${LIBXML2_LIBRARIES}
)

add_library(cogsys_rlmdl
  src/rl/mdl/Body.h
  src/rl/mdl/Compound.h
  src/rl/mdl/Cylindrical.h
  src/rl/mdl/Dynamic.h
  src/rl/mdl/Element.h
  src/rl/mdl/Exception.h
  src/rl/mdl/Factory.h
  src/rl/mdl/Fixed.h
  src/rl/mdl/Frame.h
  src/rl/mdl/Helical.h
  src/rl/mdl/Joint.h
  src/rl/mdl/Kinematic.h
  src/rl/mdl/Metric.h
  src/rl/mdl/Model.h
  src/rl/mdl/Prismatic.h
  src/rl/mdl/Revolute.h
  src/rl/mdl/Spherical.h
  src/rl/mdl/Transform.h
  src/rl/mdl/World.h
  src/rl/mdl/XmlFactory.h
  src/rl/mdl/Body.cpp
  src/rl/mdl/Compound.cpp
  src/rl/mdl/Cylindrical.cpp
  src/rl/mdl/Dynamic.cpp
  src/rl/mdl/Element.cpp
  src/rl/mdl/Exception.cpp
  src/rl/mdl/Fixed.cpp
  src/rl/mdl/Factory.cpp
  src/rl/mdl/Frame.cpp
  src/rl/mdl/Helical.cpp
  src/rl/mdl/Joint.cpp
  src/rl/mdl/Kinematic.cpp
  src/rl/mdl/Metric.cpp
  src/rl/mdl/Model.cpp
  src/rl/mdl/Prismatic.cpp
  src/rl/mdl/Revolute.cpp
  src/rl/mdl/Spherical.cpp
  src/rl/mdl/Transform.cpp
  src/rl/mdl/World.cpp
  src/rl/mdl/XmlFactory.cpp
)

target_link_libraries(
  cogsys_rlmdl
  cogsys_rlxml
  cogsys_rlmath
)

add_library(cogsys_rlutil
  src/rl/util/Exception.h
  src/rl/util/Mutex.h
  src/rl/util/MutexLocker.h
  src/rl/util/MutexTryLocker.h
  src/rl/util/Process.h
  src/rl/util/Semaphore.h
  src/rl/util/Thread.h
  src/rl/util/Timer.h
  src/rl/util/dummy.cpp
)

add_library(cogsys_rlsg
  src/rl/sg/Body.h
  src/rl/sg/DepthScene.h
  src/rl/sg/DistanceScene.h
  src/rl/sg/Exception.h
  src/rl/sg/Model.h
  src/rl/sg/RaycastScene.h
  src/rl/sg/Scene.h
  src/rl/sg/Shape.h
  src/rl/sg/SimpleScene.h
  src/rl/sg/Body.cpp
  src/rl/sg/DepthScene.cpp
  src/rl/sg/DistanceScene.cpp
  src/rl/sg/Exception.cpp
  src/rl/sg/Model.cpp
  src/rl/sg/RaycastScene.cpp
  src/rl/sg/Scene.cpp
  src/rl/sg/Shape.cpp
  src/rl/sg/SimpleScene.cpp
  src/rl/sg/bullet/Body.h
  src/rl/sg/bullet/Model.h
  src/rl/sg/bullet/Scene.h
  src/rl/sg/bullet/Shape.h
  src/rl/sg/bullet/Body.cpp
  src/rl/sg/bullet/Model.cpp
  src/rl/sg/bullet/Scene.cpp
  src/rl/sg/bullet/Shape.cpp
  src/rl/sg/so/Body.h
  src/rl/sg/so/Model.h
  src/rl/sg/so/Scene.h
  src/rl/sg/so/Shape.h
  src/rl/sg/so/Body.cpp
  src/rl/sg/so/Model.cpp
  src/rl/sg/so/Scene.cpp
  src/rl/sg/so/Shape.cpp
  src/rl/sg/ode/Body.h
  src/rl/sg/ode/Model.h
  src/rl/sg/ode/Scene.h
  src/rl/sg/ode/Shape.h
  src/rl/sg/ode/Body.cpp
  src/rl/sg/ode/Model.cpp
  src/rl/sg/ode/Scene.cpp
  src/rl/sg/ode/Shape.cpp
  #src/rl/sg/pqp/Model.h
  #src/rl/sg/pqp/Scene.h
  #src/rl/sg/pqp/Shape.h
  #src/rl/sg/pqp/Body.cpp
  #src/rl/sg/pqp/Model.cpp
  #src/rl/sg/pqp/Scene.cpp
  #src/rl/sg/pqp/Shape.cpp
  src/rl/sg/solid/Body.h
  src/rl/sg/solid/Model.h
  src/rl/sg/solid/Scene.h
  src/rl/sg/solid/Shape.h
  src/rl/sg/solid/Body.cpp
  src/rl/sg/solid/Model.cpp
  src/rl/sg/solid/Scene.cpp
  src/rl/sg/solid/Shape.cpp
)

target_link_libraries(
  cogsys_rlsg 
  cogsys_rlxml
  cogsys_rlutil
  ${BULLET_LIBRARIES}
  ${ODE_LIBRARIES}
  ${SOLID_LIBRARIES}
)

## Declare a cpp executable
add_executable(cogsys_visualization_node ${MOC_SRCS} ${HDRS} ${SRCS})

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(cogsys_visualization_node cogsys_visualization_generate_messages_cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(cogsys_visualization_node
   ${catkin_LIBRARIES}
   ${Boost_LIBRARIES}
   ${LIBXML2_LIBRARIES}
#   ${RL_LIBRARIES}
   ${COIN_LIBRARIES}
   ${QT_LIBRARIES}
   ${OPENGL_LIBRARIES}
   ${SOQT_LIBRARIES}
   cogsys_rlmath
   cogsys_rlsg
   cogsys_rlmdl
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS cogsys_visualization cogsys_visualization_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_cogsys_visualization.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
