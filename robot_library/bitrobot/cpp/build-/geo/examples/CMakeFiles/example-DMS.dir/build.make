# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /home/lovezy/packs/cmake-3.17.5-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/lovezy/packs/cmake-3.17.5-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo

# Include any dependencies generated for this target.
include examples/CMakeFiles/example-DMS.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/example-DMS.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/example-DMS.dir/flags.make

examples/CMakeFiles/example-DMS.dir/example-DMS.cpp.o: examples/CMakeFiles/example-DMS.dir/flags.make
examples/CMakeFiles/example-DMS.dir/example-DMS.cpp.o: /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/examples/example-DMS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/example-DMS.dir/example-DMS.cpp.o"
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example-DMS.dir/example-DMS.cpp.o -c /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/examples/example-DMS.cpp

examples/CMakeFiles/example-DMS.dir/example-DMS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example-DMS.dir/example-DMS.cpp.i"
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/examples/example-DMS.cpp > CMakeFiles/example-DMS.dir/example-DMS.cpp.i

examples/CMakeFiles/example-DMS.dir/example-DMS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example-DMS.dir/example-DMS.cpp.s"
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/examples/example-DMS.cpp -o CMakeFiles/example-DMS.dir/example-DMS.cpp.s

# Object files for target example-DMS
example__DMS_OBJECTS = \
"CMakeFiles/example-DMS.dir/example-DMS.cpp.o"

# External object files for target example-DMS
example__DMS_EXTERNAL_OBJECTS =

examples/example-DMS: examples/CMakeFiles/example-DMS.dir/example-DMS.cpp.o
examples/example-DMS: examples/CMakeFiles/example-DMS.dir/build.make
examples/example-DMS: src/libGeographic.so.17.0.0
examples/example-DMS: examples/CMakeFiles/example-DMS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable example-DMS"
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example-DMS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/example-DMS.dir/build: examples/example-DMS

.PHONY : examples/CMakeFiles/example-DMS.dir/build

examples/CMakeFiles/example-DMS.dir/clean:
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples && $(CMAKE_COMMAND) -P CMakeFiles/example-DMS.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/example-DMS.dir/clean

examples/CMakeFiles/example-DMS.dir/depend:
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46 /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/examples /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples/CMakeFiles/example-DMS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/example-DMS.dir/depend

