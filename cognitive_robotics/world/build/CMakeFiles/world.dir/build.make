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
CMAKE_SOURCE_DIR = /home/diego/fuerte_workspace/sandbox/Cognitive/world

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/diego/fuerte_workspace/sandbox/Cognitive/world/build

# Include any dependencies generated for this target.
include CMakeFiles/world.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/world.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/world.dir/flags.make

CMakeFiles/world.dir/src/main.o: CMakeFiles/world.dir/flags.make
CMakeFiles/world.dir/src/main.o: ../src/main.cpp
CMakeFiles/world.dir/src/main.o: ../manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/stacks/bullet/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/geometry_msgs/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/sensor_msgs/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/roslang/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/roscpp/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/rosconsole/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/stacks/geometry/angles/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/rospy/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/rostest/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/roswtf/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/message_filters/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/stacks/geometry/tf/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/ros/core/rosbuild/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/roslib/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/stacks/pluginlib/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/stacks/image_common/image_transport/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/std_msgs/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/stacks/vision_opencv/opencv2/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/stacks/vision_opencv/cv_bridge/manifest.xml
CMakeFiles/world.dir/src/main.o: /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/share/rosbag/manifest.xml
CMakeFiles/world.dir/src/main.o: /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/manifest.xml
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/stacks/geometry/tf/msg_gen/generated
CMakeFiles/world.dir/src/main.o: /opt/ros/fuerte/stacks/geometry/tf/srv_gen/generated
CMakeFiles/world.dir/src/main.o: /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/srv_gen/generated
CMakeFiles/world.dir/src/main.o: /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/msg_gen/generated
CMakeFiles/world.dir/src/main.o: /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/srv_gen/generated
	$(CMAKE_COMMAND) -E cmake_progress_report /home/diego/fuerte_workspace/sandbox/Cognitive/world/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/world.dir/src/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/world.dir/src/main.o -c /home/diego/fuerte_workspace/sandbox/Cognitive/world/src/main.cpp

CMakeFiles/world.dir/src/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/world.dir/src/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/diego/fuerte_workspace/sandbox/Cognitive/world/src/main.cpp > CMakeFiles/world.dir/src/main.i

CMakeFiles/world.dir/src/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/world.dir/src/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/diego/fuerte_workspace/sandbox/Cognitive/world/src/main.cpp -o CMakeFiles/world.dir/src/main.s

CMakeFiles/world.dir/src/main.o.requires:
.PHONY : CMakeFiles/world.dir/src/main.o.requires

CMakeFiles/world.dir/src/main.o.provides: CMakeFiles/world.dir/src/main.o.requires
	$(MAKE) -f CMakeFiles/world.dir/build.make CMakeFiles/world.dir/src/main.o.provides.build
.PHONY : CMakeFiles/world.dir/src/main.o.provides

CMakeFiles/world.dir/src/main.o.provides.build: CMakeFiles/world.dir/src/main.o

# Object files for target world
world_OBJECTS = \
"CMakeFiles/world.dir/src/main.o"

# External object files for target world
world_EXTERNAL_OBJECTS =

../bin/world: CMakeFiles/world.dir/src/main.o
../bin/world: CMakeFiles/world.dir/build.make
../bin/world: CMakeFiles/world.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/world"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/world.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/world.dir/build: ../bin/world
.PHONY : CMakeFiles/world.dir/build

CMakeFiles/world.dir/requires: CMakeFiles/world.dir/src/main.o.requires
.PHONY : CMakeFiles/world.dir/requires

CMakeFiles/world.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/world.dir/cmake_clean.cmake
.PHONY : CMakeFiles/world.dir/clean

CMakeFiles/world.dir/depend:
	cd /home/diego/fuerte_workspace/sandbox/Cognitive/world/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diego/fuerte_workspace/sandbox/Cognitive/world /home/diego/fuerte_workspace/sandbox/Cognitive/world /home/diego/fuerte_workspace/sandbox/Cognitive/world/build /home/diego/fuerte_workspace/sandbox/Cognitive/world/build /home/diego/fuerte_workspace/sandbox/Cognitive/world/build/CMakeFiles/world.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/world.dir/depend
