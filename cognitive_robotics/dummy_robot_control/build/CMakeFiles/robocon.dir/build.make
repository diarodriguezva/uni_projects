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
CMAKE_SOURCE_DIR = /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/build

# Include any dependencies generated for this target.
include CMakeFiles/robocon.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/robocon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/robocon.dir/flags.make

CMakeFiles/robocon.dir/src/main.o: CMakeFiles/robocon.dir/flags.make
CMakeFiles/robocon.dir/src/main.o: ../src/main.cpp
CMakeFiles/robocon.dir/src/main.o: ../manifest.xml
CMakeFiles/robocon.dir/src/main.o: /opt/ros/fuerte/share/roslang/manifest.xml
CMakeFiles/robocon.dir/src/main.o: /opt/ros/fuerte/share/roscpp/manifest.xml
	$(CMAKE_COMMAND) -E cmake_progress_report /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/robocon.dir/src/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/robocon.dir/src/main.o -c /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/src/main.cpp

CMakeFiles/robocon.dir/src/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robocon.dir/src/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/src/main.cpp > CMakeFiles/robocon.dir/src/main.i

CMakeFiles/robocon.dir/src/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robocon.dir/src/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/src/main.cpp -o CMakeFiles/robocon.dir/src/main.s

CMakeFiles/robocon.dir/src/main.o.requires:
.PHONY : CMakeFiles/robocon.dir/src/main.o.requires

CMakeFiles/robocon.dir/src/main.o.provides: CMakeFiles/robocon.dir/src/main.o.requires
	$(MAKE) -f CMakeFiles/robocon.dir/build.make CMakeFiles/robocon.dir/src/main.o.provides.build
.PHONY : CMakeFiles/robocon.dir/src/main.o.provides

CMakeFiles/robocon.dir/src/main.o.provides.build: CMakeFiles/robocon.dir/src/main.o

# Object files for target robocon
robocon_OBJECTS = \
"CMakeFiles/robocon.dir/src/main.o"

# External object files for target robocon
robocon_EXTERNAL_OBJECTS =

../bin/robocon: CMakeFiles/robocon.dir/src/main.o
../bin/robocon: CMakeFiles/robocon.dir/build.make
../bin/robocon: CMakeFiles/robocon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/robocon"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/robocon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/robocon.dir/build: ../bin/robocon
.PHONY : CMakeFiles/robocon.dir/build

CMakeFiles/robocon.dir/requires: CMakeFiles/robocon.dir/src/main.o.requires
.PHONY : CMakeFiles/robocon.dir/requires

CMakeFiles/robocon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/robocon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/robocon.dir/clean

CMakeFiles/robocon.dir/depend:
	cd /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/build /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/build /home/diego/fuerte_workspace/sandbox/Cognitive/dummy_robot_control/build/CMakeFiles/robocon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/robocon.dir/depend

