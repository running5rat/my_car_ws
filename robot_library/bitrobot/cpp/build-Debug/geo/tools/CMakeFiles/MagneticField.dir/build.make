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
CMAKE_COMMAND = /home/lovebc/Desktop/workspace/packs/cmake-3.17.5-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/lovebc/Desktop/workspace/packs/cmake-3.17.5-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo

# Include any dependencies generated for this target.
include tools/CMakeFiles/MagneticField.dir/depend.make

# Include the progress variables for this target.
include tools/CMakeFiles/MagneticField.dir/progress.make

# Include the compile flags for this target's objects.
include tools/CMakeFiles/MagneticField.dir/flags.make

tools/CMakeFiles/MagneticField.dir/MagneticField.cpp.o: tools/CMakeFiles/MagneticField.dir/flags.make
tools/CMakeFiles/MagneticField.dir/MagneticField.cpp.o: /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/tools/MagneticField.cpp
tools/CMakeFiles/MagneticField.dir/MagneticField.cpp.o: man/MagneticField.usage
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/CMakeFiles/MagneticField.dir/MagneticField.cpp.o"
	cd /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo/tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MagneticField.dir/MagneticField.cpp.o -c /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/tools/MagneticField.cpp

tools/CMakeFiles/MagneticField.dir/MagneticField.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MagneticField.dir/MagneticField.cpp.i"
	cd /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo/tools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/tools/MagneticField.cpp > CMakeFiles/MagneticField.dir/MagneticField.cpp.i

tools/CMakeFiles/MagneticField.dir/MagneticField.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MagneticField.dir/MagneticField.cpp.s"
	cd /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo/tools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/tools/MagneticField.cpp -o CMakeFiles/MagneticField.dir/MagneticField.cpp.s

# Object files for target MagneticField
MagneticField_OBJECTS = \
"CMakeFiles/MagneticField.dir/MagneticField.cpp.o"

# External object files for target MagneticField
MagneticField_EXTERNAL_OBJECTS =

tools/MagneticField: tools/CMakeFiles/MagneticField.dir/MagneticField.cpp.o
tools/MagneticField: tools/CMakeFiles/MagneticField.dir/build.make
tools/MagneticField: src/libGeographic.so.17.0.0
tools/MagneticField: tools/CMakeFiles/MagneticField.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MagneticField"
	cd /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MagneticField.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/CMakeFiles/MagneticField.dir/build: tools/MagneticField

.PHONY : tools/CMakeFiles/MagneticField.dir/build

tools/CMakeFiles/MagneticField.dir/clean:
	cd /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo/tools && $(CMAKE_COMMAND) -P CMakeFiles/MagneticField.dir/cmake_clean.cmake
.PHONY : tools/CMakeFiles/MagneticField.dir/clean

tools/CMakeFiles/MagneticField.dir/depend:
	cd /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46 /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/Bitctrl/GeographicLib-1.46/tools /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo/tools /home/lovebc/Desktop/workspace/ros/lab_car_ws/src/bitrobot/lib/repo-v0.0.4/cpp/build-Debug/geo/tools/CMakeFiles/MagneticField.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/CMakeFiles/MagneticField.dir/depend

