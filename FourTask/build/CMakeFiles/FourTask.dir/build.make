# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/918/bin/cmake

# The command to remove a file.
RM = /snap/cmake/918/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/andrew/Рабочий стол/OOP(C++)/FourTask"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/andrew/Рабочий стол/OOP(C++)/FourTask/build"

# Include any dependencies generated for this target.
include CMakeFiles/FourTask.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FourTask.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FourTask.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FourTask.dir/flags.make

CMakeFiles/FourTask.dir/main.cpp.o: CMakeFiles/FourTask.dir/flags.make
CMakeFiles/FourTask.dir/main.cpp.o: ../main.cpp
CMakeFiles/FourTask.dir/main.cpp.o: CMakeFiles/FourTask.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/andrew/Рабочий стол/OOP(C++)/FourTask/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FourTask.dir/main.cpp.o"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FourTask.dir/main.cpp.o -MF CMakeFiles/FourTask.dir/main.cpp.o.d -o CMakeFiles/FourTask.dir/main.cpp.o -c "/home/andrew/Рабочий стол/OOP(C++)/FourTask/main.cpp"

CMakeFiles/FourTask.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FourTask.dir/main.cpp.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/andrew/Рабочий стол/OOP(C++)/FourTask/main.cpp" > CMakeFiles/FourTask.dir/main.cpp.i

CMakeFiles/FourTask.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FourTask.dir/main.cpp.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/andrew/Рабочий стол/OOP(C++)/FourTask/main.cpp" -o CMakeFiles/FourTask.dir/main.cpp.s

# Object files for target FourTask
FourTask_OBJECTS = \
"CMakeFiles/FourTask.dir/main.cpp.o"

# External object files for target FourTask
FourTask_EXTERNAL_OBJECTS =

FourTask: CMakeFiles/FourTask.dir/main.cpp.o
FourTask: CMakeFiles/FourTask.dir/build.make
FourTask: CMakeFiles/FourTask.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/andrew/Рабочий стол/OOP(C++)/FourTask/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FourTask"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FourTask.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FourTask.dir/build: FourTask
.PHONY : CMakeFiles/FourTask.dir/build

CMakeFiles/FourTask.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FourTask.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FourTask.dir/clean

CMakeFiles/FourTask.dir/depend:
	cd "/home/andrew/Рабочий стол/OOP(C++)/FourTask/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/andrew/Рабочий стол/OOP(C++)/FourTask" "/home/andrew/Рабочий стол/OOP(C++)/FourTask" "/home/andrew/Рабочий стол/OOP(C++)/FourTask/build" "/home/andrew/Рабочий стол/OOP(C++)/FourTask/build" "/home/andrew/Рабочий стол/OOP(C++)/FourTask/build/CMakeFiles/FourTask.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/FourTask.dir/depend

