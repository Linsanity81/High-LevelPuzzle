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

# Utility rule file for ContinuousConfigure.

# Include the progress variables for this target.
include ext/pugixml/CMakeFiles/ContinuousConfigure.dir/progress.make

ext/pugixml/CMakeFiles/ContinuousConfigure:
	cd /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext/pugixml && /Applications/CLion.app/Contents/bin/cmake/mac/bin/ctest -D ContinuousConfigure

ContinuousConfigure: ext/pugixml/CMakeFiles/ContinuousConfigure
ContinuousConfigure: ext/pugixml/CMakeFiles/ContinuousConfigure.dir/build.make

.PHONY : ContinuousConfigure

# Rule to build all files generated by this target.
ext/pugixml/CMakeFiles/ContinuousConfigure.dir/build: ContinuousConfigure

.PHONY : ext/pugixml/CMakeFiles/ContinuousConfigure.dir/build

ext/pugixml/CMakeFiles/ContinuousConfigure.dir/clean:
	cd /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext/pugixml && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousConfigure.dir/cmake_clean.cmake
.PHONY : ext/pugixml/CMakeFiles/ContinuousConfigure.dir/clean

ext/pugixml/CMakeFiles/ContinuousConfigure.dir/depend:
	cd /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/ext/pugixml /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext/pugixml /Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/cmake-build-debug/ext/pugixml/CMakeFiles/ContinuousConfigure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ext/pugixml/CMakeFiles/ContinuousConfigure.dir/depend

