# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\JetBrains\Clion2020.1\CLion-2020.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\Clion2020.1\CLion-2020.1.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\ProblemSolving\code\project1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\ProblemSolving\code\project1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/project1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project1.dir/flags.make

CMakeFiles/project1.dir/main.cpp.obj: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\ProblemSolving\code\project1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project1.dir/main.cpp.obj"
	"D:\Program Files\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\project1.dir\main.cpp.obj -c E:\ProblemSolving\code\project1\main.cpp

CMakeFiles/project1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project1.dir/main.cpp.i"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\ProblemSolving\code\project1\main.cpp > CMakeFiles\project1.dir\main.cpp.i

CMakeFiles/project1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project1.dir/main.cpp.s"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\ProblemSolving\code\project1\main.cpp -o CMakeFiles\project1.dir\main.cpp.s

# Object files for target project1
project1_OBJECTS = \
"CMakeFiles/project1.dir/main.cpp.obj"

# External object files for target project1
project1_EXTERNAL_OBJECTS =

project1.exe: CMakeFiles/project1.dir/main.cpp.obj
project1.exe: CMakeFiles/project1.dir/build.make
project1.exe: CMakeFiles/project1.dir/linklibs.rsp
project1.exe: CMakeFiles/project1.dir/objects1.rsp
project1.exe: CMakeFiles/project1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\ProblemSolving\code\project1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable project1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\project1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project1.dir/build: project1.exe

.PHONY : CMakeFiles/project1.dir/build

CMakeFiles/project1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\project1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/project1.dir/clean

CMakeFiles/project1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\ProblemSolving\code\project1 E:\ProblemSolving\code\project1 E:\ProblemSolving\code\project1\cmake-build-debug E:\ProblemSolving\code\project1\cmake-build-debug E:\ProblemSolving\code\project1\cmake-build-debug\CMakeFiles\project1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project1.dir/depend

