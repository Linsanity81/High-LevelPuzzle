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
include ext/CMakeFiles/imguizmo.dir/depend.make

# Include the progress variables for this target.
include ext/CMakeFiles/imguizmo.dir/progress.make

# Include the compile flags for this target's objects.
include ext/CMakeFiles/imguizmo.dir/flags.make

ext/CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.o: ext/CMakeFiles/imguizmo.dir/flags.make
ext/CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.o: ../ext/libigl/external/imguizmo/ImGuizmo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ext/CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.o"
	cd /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.o -c /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/ext/libigl/external/imguizmo/ImGuizmo.cpp

ext/CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.i"
	cd /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/ext/libigl/external/imguizmo/ImGuizmo.cpp > CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.i

ext/CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.s"
	cd /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/ext/libigl/external/imguizmo/ImGuizmo.cpp -o CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.s

# Object files for target imguizmo
imguizmo_OBJECTS = \
"CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.o"

# External object files for target imguizmo
imguizmo_EXTERNAL_OBJECTS =

ext/libimguizmo.dylib: ext/CMakeFiles/imguizmo.dir/libigl/external/imguizmo/ImGuizmo.cpp.o
ext/libimguizmo.dylib: ext/CMakeFiles/imguizmo.dir/build.make
ext/libimguizmo.dylib: ext/imgui/libimgui.dylib
ext/libimguizmo.dylib: ext/CMakeFiles/imguizmo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libimguizmo.dylib"
	cd /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imguizmo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ext/CMakeFiles/imguizmo.dir/build: ext/libimguizmo.dylib

.PHONY : ext/CMakeFiles/imguizmo.dir/build

ext/CMakeFiles/imguizmo.dir/clean:
	cd /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext && $(CMAKE_COMMAND) -P CMakeFiles/imguizmo.dir/cmake_clean.cmake
.PHONY : ext/CMakeFiles/imguizmo.dir/clean

ext/CMakeFiles/imguizmo.dir/depend:
	cd /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/ext /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext/CMakeFiles/imguizmo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ext/CMakeFiles/imguizmo.dir/depend

