# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maker/build/librealsense_sdk/samples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maker/build/librealsense_sdk/samples/build

# Include any dependencies generated for this target.
include playback_sample/CMakeFiles/rs_playback_sample.dir/depend.make

# Include the progress variables for this target.
include playback_sample/CMakeFiles/rs_playback_sample.dir/progress.make

# Include the compile flags for this target's objects.
include playback_sample/CMakeFiles/rs_playback_sample.dir/flags.make

playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o: playback_sample/CMakeFiles/rs_playback_sample.dir/flags.make
playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o: ../playback_sample/playback_sample.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maker/build/librealsense_sdk/samples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o"
	cd /home/maker/build/librealsense_sdk/samples/build/playback_sample && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o -c /home/maker/build/librealsense_sdk/samples/playback_sample/playback_sample.cpp

playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.i"
	cd /home/maker/build/librealsense_sdk/samples/build/playback_sample && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maker/build/librealsense_sdk/samples/playback_sample/playback_sample.cpp > CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.i

playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.s"
	cd /home/maker/build/librealsense_sdk/samples/build/playback_sample && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maker/build/librealsense_sdk/samples/playback_sample/playback_sample.cpp -o CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.s

playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o.requires:

.PHONY : playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o.requires

playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o.provides: playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o.requires
	$(MAKE) -f playback_sample/CMakeFiles/rs_playback_sample.dir/build.make playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o.provides.build
.PHONY : playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o.provides

playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o.provides.build: playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o


# Object files for target rs_playback_sample
rs_playback_sample_OBJECTS = \
"CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o"

# External object files for target rs_playback_sample
rs_playback_sample_EXTERNAL_OBJECTS =

../bin/debug/rs_playback_sample: playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o
../bin/debug/rs_playback_sample: playback_sample/CMakeFiles/rs_playback_sample.dir/build.make
../bin/debug/rs_playback_sample: playback_sample/CMakeFiles/rs_playback_sample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maker/build/librealsense_sdk/samples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/debug/rs_playback_sample"
	cd /home/maker/build/librealsense_sdk/samples/build/playback_sample && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rs_playback_sample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
playback_sample/CMakeFiles/rs_playback_sample.dir/build: ../bin/debug/rs_playback_sample

.PHONY : playback_sample/CMakeFiles/rs_playback_sample.dir/build

playback_sample/CMakeFiles/rs_playback_sample.dir/requires: playback_sample/CMakeFiles/rs_playback_sample.dir/playback_sample.cpp.o.requires

.PHONY : playback_sample/CMakeFiles/rs_playback_sample.dir/requires

playback_sample/CMakeFiles/rs_playback_sample.dir/clean:
	cd /home/maker/build/librealsense_sdk/samples/build/playback_sample && $(CMAKE_COMMAND) -P CMakeFiles/rs_playback_sample.dir/cmake_clean.cmake
.PHONY : playback_sample/CMakeFiles/rs_playback_sample.dir/clean

playback_sample/CMakeFiles/rs_playback_sample.dir/depend:
	cd /home/maker/build/librealsense_sdk/samples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maker/build/librealsense_sdk/samples /home/maker/build/librealsense_sdk/samples/playback_sample /home/maker/build/librealsense_sdk/samples/build /home/maker/build/librealsense_sdk/samples/build/playback_sample /home/maker/build/librealsense_sdk/samples/build/playback_sample/CMakeFiles/rs_playback_sample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : playback_sample/CMakeFiles/rs_playback_sample.dir/depend
