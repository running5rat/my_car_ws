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
include examples/CMakeFiles/example-GeographicErr.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/example-GeographicErr.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/example-GeographicErr.dir/flags.make

examples/CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.o: examples/CMakeFiles/example-GeographicErr.dir/flags.make
examples/CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.o: /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/examples/example-GeographicErr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.o"
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.o -c /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/examples/example-GeographicErr.cpp

examples/CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.i"
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/examples/example-GeographicErr.cpp > CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.i

examples/CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.s"
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/examples/example-GeographicErr.cpp -o CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.s

# Object files for target example-GeographicErr
example__GeographicErr_OBJECTS = \
"CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.o"

# External object files for target example-GeographicErr
example__GeographicErr_EXTERNAL_OBJECTS =

examples/example-GeographicErr: examples/CMakeFiles/example-GeographicErr.dir/example-GeographicErr.cpp.o
examples/example-GeographicErr: examples/CMakeFiles/example-GeographicErr.dir/build.make
examples/example-GeographicErr: src/libGeographic.so.17.0.0
examples/example-GeographicErr: examples/CMakeFiles/example-GeographicErr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable example-GeographicErr"
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example-GeographicErr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/example-GeographicErr.dir/build: examples/example-GeographicErr

.PHONY : examples/CMakeFiles/example-GeographicErr.dir/build

examples/CMakeFiles/example-GeographicErr.dir/clean:
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples && $(CMAKE_COMMAND) -P CMakeFiles/example-GeographicErr.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/example-GeographicErr.dir/clean

examples/CMakeFiles/example-GeographicErr.dir/depend:
	cd /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46 /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/examples /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples /home/lovezy/catkin_car/src/bitrobot/lib/repo-v0.0.4/cpp/build-/geo/examples/CMakeFiles/example-GeographicErr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/example-GeographicErr.dir/depend

