# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zhouxudong/Desktop/Lab/Graphic/raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build

# Include any dependencies generated for this target.
include CMakeFiles/RayTracing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RayTracing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RayTracing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RayTracing.dir/flags.make

CMakeFiles/RayTracing.dir/main.cpp.o: CMakeFiles/RayTracing.dir/flags.make
CMakeFiles/RayTracing.dir/main.cpp.o: /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/main.cpp
CMakeFiles/RayTracing.dir/main.cpp.o: CMakeFiles/RayTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RayTracing.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracing.dir/main.cpp.o -MF CMakeFiles/RayTracing.dir/main.cpp.o.d -o CMakeFiles/RayTracing.dir/main.cpp.o -c /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/main.cpp

CMakeFiles/RayTracing.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RayTracing.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/main.cpp > CMakeFiles/RayTracing.dir/main.cpp.i

CMakeFiles/RayTracing.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RayTracing.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/main.cpp -o CMakeFiles/RayTracing.dir/main.cpp.s

CMakeFiles/RayTracing.dir/Vector.cpp.o: CMakeFiles/RayTracing.dir/flags.make
CMakeFiles/RayTracing.dir/Vector.cpp.o: /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Vector.cpp
CMakeFiles/RayTracing.dir/Vector.cpp.o: CMakeFiles/RayTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RayTracing.dir/Vector.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracing.dir/Vector.cpp.o -MF CMakeFiles/RayTracing.dir/Vector.cpp.o.d -o CMakeFiles/RayTracing.dir/Vector.cpp.o -c /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Vector.cpp

CMakeFiles/RayTracing.dir/Vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RayTracing.dir/Vector.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Vector.cpp > CMakeFiles/RayTracing.dir/Vector.cpp.i

CMakeFiles/RayTracing.dir/Vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RayTracing.dir/Vector.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Vector.cpp -o CMakeFiles/RayTracing.dir/Vector.cpp.s

CMakeFiles/RayTracing.dir/Object.cpp.o: CMakeFiles/RayTracing.dir/flags.make
CMakeFiles/RayTracing.dir/Object.cpp.o: /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Object.cpp
CMakeFiles/RayTracing.dir/Object.cpp.o: CMakeFiles/RayTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/RayTracing.dir/Object.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracing.dir/Object.cpp.o -MF CMakeFiles/RayTracing.dir/Object.cpp.o.d -o CMakeFiles/RayTracing.dir/Object.cpp.o -c /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Object.cpp

CMakeFiles/RayTracing.dir/Object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RayTracing.dir/Object.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Object.cpp > CMakeFiles/RayTracing.dir/Object.cpp.i

CMakeFiles/RayTracing.dir/Object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RayTracing.dir/Object.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Object.cpp -o CMakeFiles/RayTracing.dir/Object.cpp.s

CMakeFiles/RayTracing.dir/Mesh.cpp.o: CMakeFiles/RayTracing.dir/flags.make
CMakeFiles/RayTracing.dir/Mesh.cpp.o: /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Mesh.cpp
CMakeFiles/RayTracing.dir/Mesh.cpp.o: CMakeFiles/RayTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/RayTracing.dir/Mesh.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracing.dir/Mesh.cpp.o -MF CMakeFiles/RayTracing.dir/Mesh.cpp.o.d -o CMakeFiles/RayTracing.dir/Mesh.cpp.o -c /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Mesh.cpp

CMakeFiles/RayTracing.dir/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RayTracing.dir/Mesh.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Mesh.cpp > CMakeFiles/RayTracing.dir/Mesh.cpp.i

CMakeFiles/RayTracing.dir/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RayTracing.dir/Mesh.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Mesh.cpp -o CMakeFiles/RayTracing.dir/Mesh.cpp.s

CMakeFiles/RayTracing.dir/Scene.cpp.o: CMakeFiles/RayTracing.dir/flags.make
CMakeFiles/RayTracing.dir/Scene.cpp.o: /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Scene.cpp
CMakeFiles/RayTracing.dir/Scene.cpp.o: CMakeFiles/RayTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/RayTracing.dir/Scene.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracing.dir/Scene.cpp.o -MF CMakeFiles/RayTracing.dir/Scene.cpp.o.d -o CMakeFiles/RayTracing.dir/Scene.cpp.o -c /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Scene.cpp

CMakeFiles/RayTracing.dir/Scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RayTracing.dir/Scene.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Scene.cpp > CMakeFiles/RayTracing.dir/Scene.cpp.i

CMakeFiles/RayTracing.dir/Scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RayTracing.dir/Scene.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Scene.cpp -o CMakeFiles/RayTracing.dir/Scene.cpp.s

CMakeFiles/RayTracing.dir/BVH.cpp.o: CMakeFiles/RayTracing.dir/flags.make
CMakeFiles/RayTracing.dir/BVH.cpp.o: /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/BVH.cpp
CMakeFiles/RayTracing.dir/BVH.cpp.o: CMakeFiles/RayTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/RayTracing.dir/BVH.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracing.dir/BVH.cpp.o -MF CMakeFiles/RayTracing.dir/BVH.cpp.o.d -o CMakeFiles/RayTracing.dir/BVH.cpp.o -c /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/BVH.cpp

CMakeFiles/RayTracing.dir/BVH.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RayTracing.dir/BVH.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/BVH.cpp > CMakeFiles/RayTracing.dir/BVH.cpp.i

CMakeFiles/RayTracing.dir/BVH.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RayTracing.dir/BVH.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/BVH.cpp -o CMakeFiles/RayTracing.dir/BVH.cpp.s

CMakeFiles/RayTracing.dir/BoundingBox.cpp.o: CMakeFiles/RayTracing.dir/flags.make
CMakeFiles/RayTracing.dir/BoundingBox.cpp.o: /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/BoundingBox.cpp
CMakeFiles/RayTracing.dir/BoundingBox.cpp.o: CMakeFiles/RayTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/RayTracing.dir/BoundingBox.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracing.dir/BoundingBox.cpp.o -MF CMakeFiles/RayTracing.dir/BoundingBox.cpp.o.d -o CMakeFiles/RayTracing.dir/BoundingBox.cpp.o -c /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/BoundingBox.cpp

CMakeFiles/RayTracing.dir/BoundingBox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RayTracing.dir/BoundingBox.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/BoundingBox.cpp > CMakeFiles/RayTracing.dir/BoundingBox.cpp.i

CMakeFiles/RayTracing.dir/BoundingBox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RayTracing.dir/BoundingBox.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/BoundingBox.cpp -o CMakeFiles/RayTracing.dir/BoundingBox.cpp.s

CMakeFiles/RayTracing.dir/Ray.cpp.o: CMakeFiles/RayTracing.dir/flags.make
CMakeFiles/RayTracing.dir/Ray.cpp.o: /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Ray.cpp
CMakeFiles/RayTracing.dir/Ray.cpp.o: CMakeFiles/RayTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/RayTracing.dir/Ray.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracing.dir/Ray.cpp.o -MF CMakeFiles/RayTracing.dir/Ray.cpp.o.d -o CMakeFiles/RayTracing.dir/Ray.cpp.o -c /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Ray.cpp

CMakeFiles/RayTracing.dir/Ray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RayTracing.dir/Ray.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Ray.cpp > CMakeFiles/RayTracing.dir/Ray.cpp.i

CMakeFiles/RayTracing.dir/Ray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RayTracing.dir/Ray.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Ray.cpp -o CMakeFiles/RayTracing.dir/Ray.cpp.s

CMakeFiles/RayTracing.dir/Material.cpp.o: CMakeFiles/RayTracing.dir/flags.make
CMakeFiles/RayTracing.dir/Material.cpp.o: /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Material.cpp
CMakeFiles/RayTracing.dir/Material.cpp.o: CMakeFiles/RayTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/RayTracing.dir/Material.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracing.dir/Material.cpp.o -MF CMakeFiles/RayTracing.dir/Material.cpp.o.d -o CMakeFiles/RayTracing.dir/Material.cpp.o -c /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Material.cpp

CMakeFiles/RayTracing.dir/Material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RayTracing.dir/Material.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Material.cpp > CMakeFiles/RayTracing.dir/Material.cpp.i

CMakeFiles/RayTracing.dir/Material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RayTracing.dir/Material.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Material.cpp -o CMakeFiles/RayTracing.dir/Material.cpp.s

CMakeFiles/RayTracing.dir/Renderer.cpp.o: CMakeFiles/RayTracing.dir/flags.make
CMakeFiles/RayTracing.dir/Renderer.cpp.o: /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Renderer.cpp
CMakeFiles/RayTracing.dir/Renderer.cpp.o: CMakeFiles/RayTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/RayTracing.dir/Renderer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracing.dir/Renderer.cpp.o -MF CMakeFiles/RayTracing.dir/Renderer.cpp.o.d -o CMakeFiles/RayTracing.dir/Renderer.cpp.o -c /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Renderer.cpp

CMakeFiles/RayTracing.dir/Renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RayTracing.dir/Renderer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Renderer.cpp > CMakeFiles/RayTracing.dir/Renderer.cpp.i

CMakeFiles/RayTracing.dir/Renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RayTracing.dir/Renderer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/Renderer.cpp -o CMakeFiles/RayTracing.dir/Renderer.cpp.s

# Object files for target RayTracing
RayTracing_OBJECTS = \
"CMakeFiles/RayTracing.dir/main.cpp.o" \
"CMakeFiles/RayTracing.dir/Vector.cpp.o" \
"CMakeFiles/RayTracing.dir/Object.cpp.o" \
"CMakeFiles/RayTracing.dir/Mesh.cpp.o" \
"CMakeFiles/RayTracing.dir/Scene.cpp.o" \
"CMakeFiles/RayTracing.dir/BVH.cpp.o" \
"CMakeFiles/RayTracing.dir/BoundingBox.cpp.o" \
"CMakeFiles/RayTracing.dir/Ray.cpp.o" \
"CMakeFiles/RayTracing.dir/Material.cpp.o" \
"CMakeFiles/RayTracing.dir/Renderer.cpp.o"

# External object files for target RayTracing
RayTracing_EXTERNAL_OBJECTS =

RayTracing: CMakeFiles/RayTracing.dir/main.cpp.o
RayTracing: CMakeFiles/RayTracing.dir/Vector.cpp.o
RayTracing: CMakeFiles/RayTracing.dir/Object.cpp.o
RayTracing: CMakeFiles/RayTracing.dir/Mesh.cpp.o
RayTracing: CMakeFiles/RayTracing.dir/Scene.cpp.o
RayTracing: CMakeFiles/RayTracing.dir/BVH.cpp.o
RayTracing: CMakeFiles/RayTracing.dir/BoundingBox.cpp.o
RayTracing: CMakeFiles/RayTracing.dir/Ray.cpp.o
RayTracing: CMakeFiles/RayTracing.dir/Material.cpp.o
RayTracing: CMakeFiles/RayTracing.dir/Renderer.cpp.o
RayTracing: CMakeFiles/RayTracing.dir/build.make
RayTracing: CMakeFiles/RayTracing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable RayTracing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RayTracing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RayTracing.dir/build: RayTracing
.PHONY : CMakeFiles/RayTracing.dir/build

CMakeFiles/RayTracing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RayTracing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RayTracing.dir/clean

CMakeFiles/RayTracing.dir/depend:
	cd /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zhouxudong/Desktop/Lab/Graphic/raytracer /Users/zhouxudong/Desktop/Lab/Graphic/raytracer /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build /Users/zhouxudong/Desktop/Lab/Graphic/raytracer/build/CMakeFiles/RayTracing.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/RayTracing.dir/depend

