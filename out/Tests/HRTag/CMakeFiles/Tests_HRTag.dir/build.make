# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/isaiah/Documents/Programming/C++/Projects/Stabby

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/isaiah/Documents/Programming/C++/Projects/Stabby/out

# Include any dependencies generated for this target.
include Tests/HRTag/CMakeFiles/Tests_HRTag.dir/depend.make

# Include the progress variables for this target.
include Tests/HRTag/CMakeFiles/Tests_HRTag.dir/progress.make

# Include the compile flags for this target's objects.
include Tests/HRTag/CMakeFiles/Tests_HRTag.dir/flags.make

Tests/HRTag/CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.o: Tests/HRTag/CMakeFiles/Tests_HRTag.dir/flags.make
Tests/HRTag/CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.o: ../Tests/HRTag/Tests_HRTag.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaiah/Documents/Programming/C++/Projects/Stabby/out/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Tests/HRTag/CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.o"
	cd /home/isaiah/Documents/Programming/C++/Projects/Stabby/out/Tests/HRTag && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.o -c /home/isaiah/Documents/Programming/C++/Projects/Stabby/Tests/HRTag/Tests_HRTag.cpp

Tests/HRTag/CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.i"
	cd /home/isaiah/Documents/Programming/C++/Projects/Stabby/out/Tests/HRTag && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/isaiah/Documents/Programming/C++/Projects/Stabby/Tests/HRTag/Tests_HRTag.cpp > CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.i

Tests/HRTag/CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.s"
	cd /home/isaiah/Documents/Programming/C++/Projects/Stabby/out/Tests/HRTag && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/isaiah/Documents/Programming/C++/Projects/Stabby/Tests/HRTag/Tests_HRTag.cpp -o CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.s

# Object files for target Tests_HRTag
Tests_HRTag_OBJECTS = \
"CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.o"

# External object files for target Tests_HRTag
Tests_HRTag_EXTERNAL_OBJECTS =

Tests/HRTag/Tests_HRTag: Tests/HRTag/CMakeFiles/Tests_HRTag.dir/Tests_HRTag.cpp.o
Tests/HRTag/Tests_HRTag: Tests/HRTag/CMakeFiles/Tests_HRTag.dir/build.make
Tests/HRTag/Tests_HRTag: Suqua/libSuqua.a
Tests/HRTag/Tests_HRTag: enet-master/libenet.a
Tests/HRTag/Tests_HRTag: Tests/HRTag/CMakeFiles/Tests_HRTag.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/isaiah/Documents/Programming/C++/Projects/Stabby/out/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Tests_HRTag"
	cd /home/isaiah/Documents/Programming/C++/Projects/Stabby/out/Tests/HRTag && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tests_HRTag.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Tests/HRTag/CMakeFiles/Tests_HRTag.dir/build: Tests/HRTag/Tests_HRTag

.PHONY : Tests/HRTag/CMakeFiles/Tests_HRTag.dir/build

Tests/HRTag/CMakeFiles/Tests_HRTag.dir/clean:
	cd /home/isaiah/Documents/Programming/C++/Projects/Stabby/out/Tests/HRTag && $(CMAKE_COMMAND) -P CMakeFiles/Tests_HRTag.dir/cmake_clean.cmake
.PHONY : Tests/HRTag/CMakeFiles/Tests_HRTag.dir/clean

Tests/HRTag/CMakeFiles/Tests_HRTag.dir/depend:
	cd /home/isaiah/Documents/Programming/C++/Projects/Stabby/out && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/isaiah/Documents/Programming/C++/Projects/Stabby /home/isaiah/Documents/Programming/C++/Projects/Stabby/Tests/HRTag /home/isaiah/Documents/Programming/C++/Projects/Stabby/out /home/isaiah/Documents/Programming/C++/Projects/Stabby/out/Tests/HRTag /home/isaiah/Documents/Programming/C++/Projects/Stabby/out/Tests/HRTag/CMakeFiles/Tests_HRTag.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Tests/HRTag/CMakeFiles/Tests_HRTag.dir/depend
