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
include fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/depend.make

# Include the progress variables for this target.
include fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/progress.make

# Include the compile flags for this target's objects.
include fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/flags.make

fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o: fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/flags.make
fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o: ../fps_counter_sample/fps_counter_sample.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maker/build/librealsense_sdk/samples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o"
	cd /home/maker/build/librealsense_sdk/samples/build/fps_counter_sample && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o -c /home/maker/build/librealsense_sdk/samples/fps_counter_sample/fps_counter_sample.cpp

fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.i"
	cd /home/maker/build/librealsense_sdk/samples/build/fps_counter_sample && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maker/build/librealsense_sdk/samples/fps_counter_sample/fps_counter_sample.cpp > CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.i

fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.s"
	cd /home/maker/build/librealsense_sdk/samples/build/fps_counter_sample && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maker/build/librealsense_sdk/samples/fps_counter_sample/fps_counter_sample.cpp -o CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.s

fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o.requires:

.PHONY : fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o.requires

fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o.provides: fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o.requires
	$(MAKE) -f fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/build.make fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o.provides.build
.PHONY : fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o.provides

fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o.provides.build: fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o


# Object files for target rs_fps_counter_sample
rs_fps_counter_sample_OBJECTS = \
"CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o"

# External object files for target rs_fps_counter_sample
rs_fps_counter_sample_EXTERNAL_OBJECTS =

../bin/debug/rs_fps_counter_sample: fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o
../bin/debug/rs_fps_counter_sample: fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/build.make
../bin/debug/rs_fps_counter_sample: fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maker/build/librealsense_sdk/samples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/debug/rs_fps_counter_sample"
	cd /home/maker/build/librealsense_sdk/samples/build/fps_counter_sample && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rs_fps_counter_sample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/build: ../bin/debug/rs_fps_counter_sample

.PHONY : fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/build

fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/requires: fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/fps_counter_sample.cpp.o.requires

.PHONY : fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/requires

fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/clean:
	cd /home/maker/build/librealsense_sdk/samples/build/fps_counter_sample && $(CMAKE_COMMAND) -P CMakeFiles/rs_fps_counter_sample.dir/cmake_clean.cmake
.PHONY : fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/clean

fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/depend:
	cd /home/maker/build/librealsense_sdk/samples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maker/build/librealsense_sdk/samples /home/maker/build/librealsense_sdk/samples/fps_counter_sample /home/maker/build/librealsense_sdk/samples/build /home/maker/build/librealsense_sdk/samples/build/fps_counter_sample /home/maker/build/librealsense_sdk/samples/build/fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : fps_counter_sample/CMakeFiles/rs_fps_counter_sample.dir/depend

