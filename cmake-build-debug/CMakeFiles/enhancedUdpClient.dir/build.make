# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /opt/clion-2016.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2016.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/enhancedUdpClient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/enhancedUdpClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/enhancedUdpClient.dir/flags.make

CMakeFiles/enhancedUdpClient.dir/main.cpp.o: CMakeFiles/enhancedUdpClient.dir/flags.make
CMakeFiles/enhancedUdpClient.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/enhancedUdpClient.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enhancedUdpClient.dir/main.cpp.o -c /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/main.cpp

CMakeFiles/enhancedUdpClient.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enhancedUdpClient.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/main.cpp > CMakeFiles/enhancedUdpClient.dir/main.cpp.i

CMakeFiles/enhancedUdpClient.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enhancedUdpClient.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/main.cpp -o CMakeFiles/enhancedUdpClient.dir/main.cpp.s

CMakeFiles/enhancedUdpClient.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/enhancedUdpClient.dir/main.cpp.o.requires

CMakeFiles/enhancedUdpClient.dir/main.cpp.o.provides: CMakeFiles/enhancedUdpClient.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/enhancedUdpClient.dir/build.make CMakeFiles/enhancedUdpClient.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/enhancedUdpClient.dir/main.cpp.o.provides

CMakeFiles/enhancedUdpClient.dir/main.cpp.o.provides.build: CMakeFiles/enhancedUdpClient.dir/main.cpp.o


CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o: CMakeFiles/enhancedUdpClient.dir/flags.make
CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o: ../ClientSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o -c /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/ClientSocket.cpp

CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/ClientSocket.cpp > CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.i

CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/ClientSocket.cpp -o CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.s

CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o.requires:

.PHONY : CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o.requires

CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o.provides: CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o.requires
	$(MAKE) -f CMakeFiles/enhancedUdpClient.dir/build.make CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o.provides.build
.PHONY : CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o.provides

CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o.provides.build: CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o


CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o: CMakeFiles/enhancedUdpClient.dir/flags.make
CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o: ../FileWriter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o -c /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/FileWriter.cpp

CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/FileWriter.cpp > CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.i

CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/FileWriter.cpp -o CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.s

CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o.requires:

.PHONY : CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o.requires

CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o.provides: CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o.requires
	$(MAKE) -f CMakeFiles/enhancedUdpClient.dir/build.make CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o.provides.build
.PHONY : CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o.provides

CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o.provides.build: CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o


CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o: CMakeFiles/enhancedUdpClient.dir/flags.make
CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o: ../GbnReceiver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o -c /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/GbnReceiver.cpp

CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/GbnReceiver.cpp > CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.i

CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/GbnReceiver.cpp -o CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.s

CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o.requires:

.PHONY : CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o.requires

CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o.provides: CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o.requires
	$(MAKE) -f CMakeFiles/enhancedUdpClient.dir/build.make CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o.provides.build
.PHONY : CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o.provides

CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o.provides.build: CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o


# Object files for target enhancedUdpClient
enhancedUdpClient_OBJECTS = \
"CMakeFiles/enhancedUdpClient.dir/main.cpp.o" \
"CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o" \
"CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o" \
"CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o"

# External object files for target enhancedUdpClient
enhancedUdpClient_EXTERNAL_OBJECTS =

enhancedUdpClient: CMakeFiles/enhancedUdpClient.dir/main.cpp.o
enhancedUdpClient: CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o
enhancedUdpClient: CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o
enhancedUdpClient: CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o
enhancedUdpClient: CMakeFiles/enhancedUdpClient.dir/build.make
enhancedUdpClient: /usr/lib/x86_64-linux-gnu/libboost_system.so
enhancedUdpClient: /usr/lib/x86_64-linux-gnu/libboost_system.so
enhancedUdpClient: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
enhancedUdpClient: /usr/lib/x86_64-linux-gnu/libboost_thread.so
enhancedUdpClient: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
enhancedUdpClient: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
enhancedUdpClient: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
enhancedUdpClient: CMakeFiles/enhancedUdpClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable enhancedUdpClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/enhancedUdpClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/enhancedUdpClient.dir/build: enhancedUdpClient

.PHONY : CMakeFiles/enhancedUdpClient.dir/build

CMakeFiles/enhancedUdpClient.dir/requires: CMakeFiles/enhancedUdpClient.dir/main.cpp.o.requires
CMakeFiles/enhancedUdpClient.dir/requires: CMakeFiles/enhancedUdpClient.dir/ClientSocket.cpp.o.requires
CMakeFiles/enhancedUdpClient.dir/requires: CMakeFiles/enhancedUdpClient.dir/FileWriter.cpp.o.requires
CMakeFiles/enhancedUdpClient.dir/requires: CMakeFiles/enhancedUdpClient.dir/GbnReceiver.cpp.o.requires

.PHONY : CMakeFiles/enhancedUdpClient.dir/requires

CMakeFiles/enhancedUdpClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/enhancedUdpClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/enhancedUdpClient.dir/clean

CMakeFiles/enhancedUdpClient.dir/depend:
	cd /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/cmake-build-debug /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/cmake-build-debug /home/ahmed/code/c/Backup-UDP/restore0/ReliableUdpTransfer/enhancedUdpClient/cmake-build-debug/CMakeFiles/enhancedUdpClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/enhancedUdpClient.dir/depend

