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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/3DRenderlib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/3DRenderlib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/3DRenderlib.dir/flags.make

CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.o: CMakeFiles/3DRenderlib.dir/flags.make
CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.o: ../src/Render/libigl_Render.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.o -c /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/src/Render/libigl_Render.cpp

CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/src/Render/libigl_Render.cpp > CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.i

CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/src/Render/libigl_Render.cpp -o CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.s

CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.o: CMakeFiles/3DRenderlib.dir/flags.make
CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.o: ../src/Render/libigl_UI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.o -c /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/src/Render/libigl_UI.cpp

CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/src/Render/libigl_UI.cpp > CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.i

CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/src/Render/libigl_UI.cpp -o CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.s

# Object files for target 3DRenderlib
3DRenderlib_OBJECTS = \
"CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.o" \
"CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.o"

# External object files for target 3DRenderlib
3DRenderlib_EXTERNAL_OBJECTS =

lib3DRenderlib.a: CMakeFiles/3DRenderlib.dir/src/Render/libigl_Render.cpp.o
lib3DRenderlib.a: CMakeFiles/3DRenderlib.dir/src/Render/libigl_UI.cpp.o
lib3DRenderlib.a: CMakeFiles/3DRenderlib.dir/build.make
lib3DRenderlib.a: CMakeFiles/3DRenderlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library lib3DRenderlib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/3DRenderlib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/3DRenderlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/3DRenderlib.dir/build: lib3DRenderlib.a

.PHONY : CMakeFiles/3DRenderlib.dir/build

CMakeFiles/3DRenderlib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/3DRenderlib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/3DRenderlib.dir/clean

CMakeFiles/3DRenderlib.dir/depend:
	cd /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/CMakeFiles/3DRenderlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/3DRenderlib.dir/depend

