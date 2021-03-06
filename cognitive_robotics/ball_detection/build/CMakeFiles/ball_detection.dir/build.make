# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/build

# Include any dependencies generated for this target.
include CMakeFiles/ball_detection.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ball_detection.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ball_detection.dir/flags.make

CMakeFiles/ball_detection.dir/src/trackable.o: CMakeFiles/ball_detection.dir/flags.make
CMakeFiles/ball_detection.dir/src/trackable.o: ../src/trackable.cpp
CMakeFiles/ball_detection.dir/src/trackable.o: ../manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/roslang/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/roscpp/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/rospy/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/rosbag/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/stacks/bullet/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/geometry_msgs/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/sensor_msgs/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/rosconsole/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/stacks/geometry/angles/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/rostest/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/roswtf/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/message_filters/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/stacks/geometry/tf/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/ros/core/rosbuild/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/roslib/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/stacks/pluginlib/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/stacks/image_common/image_transport/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/share/std_msgs/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/stacks/vision_opencv/opencv2/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/stacks/vision_opencv/cv_bridge/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/manifest.xml
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/stacks/geometry/tf/msg_gen/generated
CMakeFiles/ball_detection.dir/src/trackable.o: /opt/ros/fuerte/stacks/geometry/tf/srv_gen/generated
CMakeFiles/ball_detection.dir/src/trackable.o: /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/srv_gen/generated
	$(CMAKE_COMMAND) -E cmake_progress_report /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ball_detection.dir/src/trackable.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/ball_detection.dir/src/trackable.o -c /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/src/trackable.cpp

CMakeFiles/ball_detection.dir/src/trackable.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ball_detection.dir/src/trackable.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/src/trackable.cpp > CMakeFiles/ball_detection.dir/src/trackable.i

CMakeFiles/ball_detection.dir/src/trackable.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ball_detection.dir/src/trackable.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/src/trackable.cpp -o CMakeFiles/ball_detection.dir/src/trackable.s

CMakeFiles/ball_detection.dir/src/trackable.o.requires:
.PHONY : CMakeFiles/ball_detection.dir/src/trackable.o.requires

CMakeFiles/ball_detection.dir/src/trackable.o.provides: CMakeFiles/ball_detection.dir/src/trackable.o.requires
	$(MAKE) -f CMakeFiles/ball_detection.dir/build.make CMakeFiles/ball_detection.dir/src/trackable.o.provides.build
.PHONY : CMakeFiles/ball_detection.dir/src/trackable.o.provides

CMakeFiles/ball_detection.dir/src/trackable.o.provides.build: CMakeFiles/ball_detection.dir/src/trackable.o

CMakeFiles/ball_detection.dir/src/main.o: CMakeFiles/ball_detection.dir/flags.make
CMakeFiles/ball_detection.dir/src/main.o: ../src/main.cpp
CMakeFiles/ball_detection.dir/src/main.o: ../manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/roslang/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/roscpp/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/rospy/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/rosbag/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/stacks/bullet/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/geometry_msgs/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/sensor_msgs/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/rosconsole/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/stacks/geometry/angles/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/rostest/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/roswtf/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/message_filters/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/stacks/geometry/tf/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/ros/core/rosbuild/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/roslib/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/stacks/pluginlib/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/stacks/image_common/image_transport/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/share/std_msgs/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/stacks/vision_opencv/opencv2/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/stacks/vision_opencv/cv_bridge/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/manifest.xml
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/stacks/geometry/tf/msg_gen/generated
CMakeFiles/ball_detection.dir/src/main.o: /opt/ros/fuerte/stacks/geometry/tf/srv_gen/generated
CMakeFiles/ball_detection.dir/src/main.o: /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/srv_gen/generated
	$(CMAKE_COMMAND) -E cmake_progress_report /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ball_detection.dir/src/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/ball_detection.dir/src/main.o -c /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/src/main.cpp

CMakeFiles/ball_detection.dir/src/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ball_detection.dir/src/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/src/main.cpp > CMakeFiles/ball_detection.dir/src/main.i

CMakeFiles/ball_detection.dir/src/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ball_detection.dir/src/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/src/main.cpp -o CMakeFiles/ball_detection.dir/src/main.s

CMakeFiles/ball_detection.dir/src/main.o.requires:
.PHONY : CMakeFiles/ball_detection.dir/src/main.o.requires

CMakeFiles/ball_detection.dir/src/main.o.provides: CMakeFiles/ball_detection.dir/src/main.o.requires
	$(MAKE) -f CMakeFiles/ball_detection.dir/build.make CMakeFiles/ball_detection.dir/src/main.o.provides.build
.PHONY : CMakeFiles/ball_detection.dir/src/main.o.provides

CMakeFiles/ball_detection.dir/src/main.o.provides.build: CMakeFiles/ball_detection.dir/src/main.o

# Object files for target ball_detection
ball_detection_OBJECTS = \
"CMakeFiles/ball_detection.dir/src/trackable.o" \
"CMakeFiles/ball_detection.dir/src/main.o"

# External object files for target ball_detection
ball_detection_EXTERNAL_OBJECTS =

../bin/ball_detection: CMakeFiles/ball_detection.dir/src/trackable.o
../bin/ball_detection: CMakeFiles/ball_detection.dir/src/main.o
../bin/ball_detection: CMakeFiles/ball_detection.dir/build.make
../bin/ball_detection: CMakeFiles/ball_detection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/ball_detection"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ball_detection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ball_detection.dir/build: ../bin/ball_detection
.PHONY : CMakeFiles/ball_detection.dir/build

CMakeFiles/ball_detection.dir/requires: CMakeFiles/ball_detection.dir/src/trackable.o.requires
CMakeFiles/ball_detection.dir/requires: CMakeFiles/ball_detection.dir/src/main.o.requires
.PHONY : CMakeFiles/ball_detection.dir/requires

CMakeFiles/ball_detection.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ball_detection.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ball_detection.dir/clean

CMakeFiles/ball_detection.dir/depend:
	cd /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/build /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/build /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/build/CMakeFiles/ball_detection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ball_detection.dir/depend

