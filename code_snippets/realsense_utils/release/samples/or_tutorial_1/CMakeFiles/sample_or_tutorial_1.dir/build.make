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
CMAKE_SOURCE_DIR = /home/ntuser/workspace/realsense_samples-0.2.10

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ntuser/workspace/realsense_samples-0.2.10/release

# Include any dependencies generated for this target.
include samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/depend.make

# Include the progress variables for this target.
include samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/progress.make

# Include the compile flags for this target's objects.
include samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/flags.make

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/flags.make
samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o: ../samples/or_tutorial_1/cpp/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ntuser/workspace/realsense_samples-0.2.10/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o"
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o -c /home/ntuser/workspace/realsense_samples-0.2.10/samples/or_tutorial_1/cpp/main.cpp

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.i"
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ntuser/workspace/realsense_samples-0.2.10/samples/or_tutorial_1/cpp/main.cpp > CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.i

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.s"
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ntuser/workspace/realsense_samples-0.2.10/samples/or_tutorial_1/cpp/main.cpp -o CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.s

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o.requires:

.PHONY : samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o.requires

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o.provides: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o.requires
	$(MAKE) -f samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/build.make samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o.provides.build
.PHONY : samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o.provides

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o.provides.build: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o


samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/flags.make
samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o: ../samples/or_tutorial_1/cpp/camera_utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ntuser/workspace/realsense_samples-0.2.10/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o"
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o -c /home/ntuser/workspace/realsense_samples-0.2.10/samples/or_tutorial_1/cpp/camera_utils.cpp

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.i"
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ntuser/workspace/realsense_samples-0.2.10/samples/or_tutorial_1/cpp/camera_utils.cpp > CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.i

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.s"
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ntuser/workspace/realsense_samples-0.2.10/samples/or_tutorial_1/cpp/camera_utils.cpp -o CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.s

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o.requires:

.PHONY : samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o.requires

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o.provides: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o.requires
	$(MAKE) -f samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/build.make samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o.provides.build
.PHONY : samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o.provides

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o.provides.build: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o


samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/flags.make
samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o: ../samples/or_tutorial_1/cpp/console_view.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ntuser/workspace/realsense_samples-0.2.10/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o"
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o -c /home/ntuser/workspace/realsense_samples-0.2.10/samples/or_tutorial_1/cpp/console_view.cpp

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.i"
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ntuser/workspace/realsense_samples-0.2.10/samples/or_tutorial_1/cpp/console_view.cpp > CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.i

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.s"
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ntuser/workspace/realsense_samples-0.2.10/samples/or_tutorial_1/cpp/console_view.cpp -o CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.s

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o.requires:

.PHONY : samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o.requires

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o.provides: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o.requires
	$(MAKE) -f samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/build.make samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o.provides.build
.PHONY : samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o.provides

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o.provides.build: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o


# Object files for target sample_or_tutorial_1
sample_or_tutorial_1_OBJECTS = \
"CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o" \
"CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o" \
"CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o"

# External object files for target sample_or_tutorial_1
sample_or_tutorial_1_EXTERNAL_OBJECTS =

samples/or_tutorial_1/sample_or_tutorial_1: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o
samples/or_tutorial_1/sample_or_tutorial_1: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o
samples/or_tutorial_1/sample_or_tutorial_1: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o
samples/or_tutorial_1/sample_or_tutorial_1: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/build.make
samples/or_tutorial_1/sample_or_tutorial_1: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ntuser/workspace/realsense_samples-0.2.10/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable sample_or_tutorial_1"
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample_or_tutorial_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/build: samples/or_tutorial_1/sample_or_tutorial_1

.PHONY : samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/build

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/requires: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/main.cpp.o.requires
samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/requires: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/camera_utils.cpp.o.requires
samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/requires: samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/cpp/console_view.cpp.o.requires

.PHONY : samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/requires

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/clean:
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 && $(CMAKE_COMMAND) -P CMakeFiles/sample_or_tutorial_1.dir/cmake_clean.cmake
.PHONY : samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/clean

samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/depend:
	cd /home/ntuser/workspace/realsense_samples-0.2.10/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ntuser/workspace/realsense_samples-0.2.10 /home/ntuser/workspace/realsense_samples-0.2.10/samples/or_tutorial_1 /home/ntuser/workspace/realsense_samples-0.2.10/release /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1 /home/ntuser/workspace/realsense_samples-0.2.10/release/samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : samples/or_tutorial_1/CMakeFiles/sample_or_tutorial_1.dir/depend

