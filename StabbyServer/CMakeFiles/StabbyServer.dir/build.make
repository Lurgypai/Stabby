# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/lurgypai/Documents/Programming/CPP/Stabby

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lurgypai/Documents/Programming/CPP/Stabby

# Include any dependencies generated for this target.
include StabbyServer/CMakeFiles/StabbyServer.dir/depend.make

# Include the progress variables for this target.
include StabbyServer/CMakeFiles/StabbyServer.dir/progress.make

# Include the compile flags for this target's objects.
include StabbyServer/CMakeFiles/StabbyServer.dir/flags.make

StabbyServer/CMakeFiles/StabbyServer.dir/StabbyServer.cpp.o: StabbyServer/CMakeFiles/StabbyServer.dir/flags.make
StabbyServer/CMakeFiles/StabbyServer.dir/StabbyServer.cpp.o: StabbyServer/StabbyServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lurgypai/Documents/Programming/CPP/Stabby/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object StabbyServer/CMakeFiles/StabbyServer.dir/StabbyServer.cpp.o"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StabbyServer.dir/StabbyServer.cpp.o -c /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/StabbyServer.cpp

StabbyServer/CMakeFiles/StabbyServer.dir/StabbyServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StabbyServer.dir/StabbyServer.cpp.i"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/StabbyServer.cpp > CMakeFiles/StabbyServer.dir/StabbyServer.cpp.i

StabbyServer/CMakeFiles/StabbyServer.dir/StabbyServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StabbyServer.dir/StabbyServer.cpp.s"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/StabbyServer.cpp -o CMakeFiles/StabbyServer.dir/StabbyServer.cpp.s

StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.o: StabbyServer/CMakeFiles/StabbyServer.dir/flags.make
StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.o: StabbyServer/player/ServerPlayerComponent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lurgypai/Documents/Programming/CPP/Stabby/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.o"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.o -c /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/player/ServerPlayerComponent.cpp

StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.i"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/player/ServerPlayerComponent.cpp > CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.i

StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.s"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/player/ServerPlayerComponent.cpp -o CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.s

StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.o: StabbyServer/CMakeFiles/StabbyServer.dir/flags.make
StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.o: StabbyServer/player/ServerPlayerSystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lurgypai/Documents/Programming/CPP/Stabby/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.o"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.o -c /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/player/ServerPlayerSystem.cpp

StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.i"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/player/ServerPlayerSystem.cpp > CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.i

StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.s"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/player/ServerPlayerSystem.cpp -o CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.s

StabbyServer/CMakeFiles/StabbyServer.dir/server/Connection.cpp.o: StabbyServer/CMakeFiles/StabbyServer.dir/flags.make
StabbyServer/CMakeFiles/StabbyServer.dir/server/Connection.cpp.o: StabbyServer/server/Connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lurgypai/Documents/Programming/CPP/Stabby/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object StabbyServer/CMakeFiles/StabbyServer.dir/server/Connection.cpp.o"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StabbyServer.dir/server/Connection.cpp.o -c /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/server/Connection.cpp

StabbyServer/CMakeFiles/StabbyServer.dir/server/Connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StabbyServer.dir/server/Connection.cpp.i"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/server/Connection.cpp > CMakeFiles/StabbyServer.dir/server/Connection.cpp.i

StabbyServer/CMakeFiles/StabbyServer.dir/server/Connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StabbyServer.dir/server/Connection.cpp.s"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/server/Connection.cpp -o CMakeFiles/StabbyServer.dir/server/Connection.cpp.s

StabbyServer/CMakeFiles/StabbyServer.dir/server/User.cpp.o: StabbyServer/CMakeFiles/StabbyServer.dir/flags.make
StabbyServer/CMakeFiles/StabbyServer.dir/server/User.cpp.o: StabbyServer/server/User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lurgypai/Documents/Programming/CPP/Stabby/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object StabbyServer/CMakeFiles/StabbyServer.dir/server/User.cpp.o"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StabbyServer.dir/server/User.cpp.o -c /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/server/User.cpp

StabbyServer/CMakeFiles/StabbyServer.dir/server/User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StabbyServer.dir/server/User.cpp.i"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/server/User.cpp > CMakeFiles/StabbyServer.dir/server/User.cpp.i

StabbyServer/CMakeFiles/StabbyServer.dir/server/User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StabbyServer.dir/server/User.cpp.s"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/server/User.cpp -o CMakeFiles/StabbyServer.dir/server/User.cpp.s

# Object files for target StabbyServer
StabbyServer_OBJECTS = \
"CMakeFiles/StabbyServer.dir/StabbyServer.cpp.o" \
"CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.o" \
"CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.o" \
"CMakeFiles/StabbyServer.dir/server/Connection.cpp.o" \
"CMakeFiles/StabbyServer.dir/server/User.cpp.o"

# External object files for target StabbyServer
StabbyServer_EXTERNAL_OBJECTS =

StabbyServer/StabbyServer: StabbyServer/CMakeFiles/StabbyServer.dir/StabbyServer.cpp.o
StabbyServer/StabbyServer: StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerComponent.cpp.o
StabbyServer/StabbyServer: StabbyServer/CMakeFiles/StabbyServer.dir/player/ServerPlayerSystem.cpp.o
StabbyServer/StabbyServer: StabbyServer/CMakeFiles/StabbyServer.dir/server/Connection.cpp.o
StabbyServer/StabbyServer: StabbyServer/CMakeFiles/StabbyServer.dir/server/User.cpp.o
StabbyServer/StabbyServer: StabbyServer/CMakeFiles/StabbyServer.dir/build.make
StabbyServer/StabbyServer: StabbyCore/libStabbyCore.a
StabbyServer/StabbyServer: enet-master/libenet.a
StabbyServer/StabbyServer: Suqua/libSuqua.a
StabbyServer/StabbyServer: StabbyServer/CMakeFiles/StabbyServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lurgypai/Documents/Programming/CPP/Stabby/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable StabbyServer"
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StabbyServer.dir/link.txt --verbose=$(VERBOSE)
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && /usr/bin/cmake -E copy_directory /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/rsrc/ /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer

# Rule to build all files generated by this target.
StabbyServer/CMakeFiles/StabbyServer.dir/build: StabbyServer/StabbyServer

.PHONY : StabbyServer/CMakeFiles/StabbyServer.dir/build

StabbyServer/CMakeFiles/StabbyServer.dir/clean:
	cd /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer && $(CMAKE_COMMAND) -P CMakeFiles/StabbyServer.dir/cmake_clean.cmake
.PHONY : StabbyServer/CMakeFiles/StabbyServer.dir/clean

StabbyServer/CMakeFiles/StabbyServer.dir/depend:
	cd /home/lurgypai/Documents/Programming/CPP/Stabby && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lurgypai/Documents/Programming/CPP/Stabby /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer /home/lurgypai/Documents/Programming/CPP/Stabby /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer /home/lurgypai/Documents/Programming/CPP/Stabby/StabbyServer/CMakeFiles/StabbyServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : StabbyServer/CMakeFiles/StabbyServer.dir/depend

