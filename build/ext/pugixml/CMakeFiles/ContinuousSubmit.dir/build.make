# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.7/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/linsanity/Documents/Github/High-LevelPuzzle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/linsanity/Documents/Github/High-LevelPuzzle/build

# Utility rule file for ContinuousSubmit.

# Include the progress variables for this target.
include ext/pugixml/CMakeFiles/ContinuousSubmit.dir/progress.make

ext/pugixml/CMakeFiles/ContinuousSubmit:
	cd /Users/linsanity/Documents/Github/High-LevelPuzzle/build/ext/pugixml && /usr/local/Cellar/cmake/3.19.7/bin/ctest -D ContinuousSubmit

ContinuousSubmit: ext/pugixml/CMakeFiles/ContinuousSubmit
ContinuousSubmit: ext/pugixml/CMakeFiles/ContinuousSubmit.dir/build.make

.PHONY : ContinuousSubmit

# Rule to build all files generated by this target.
ext/pugixml/CMakeFiles/ContinuousSubmit.dir/build: ContinuousSubmit

.PHONY : ext/pugixml/CMakeFiles/ContinuousSubmit.dir/build

ext/pugixml/CMakeFiles/ContinuousSubmit.dir/clean:
	cd /Users/linsanity/Documents/Github/High-LevelPuzzle/build/ext/pugixml && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousSubmit.dir/cmake_clean.cmake
.PHONY : ext/pugixml/CMakeFiles/ContinuousSubmit.dir/clean

ext/pugixml/CMakeFiles/ContinuousSubmit.dir/depend:
	cd /Users/linsanity/Documents/Github/High-LevelPuzzle/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/linsanity/Documents/Github/High-LevelPuzzle /Users/linsanity/Documents/Github/High-LevelPuzzle/ext/pugixml /Users/linsanity/Documents/Github/High-LevelPuzzle/build /Users/linsanity/Documents/Github/High-LevelPuzzle/build/ext/pugixml /Users/linsanity/Documents/Github/High-LevelPuzzle/build/ext/pugixml/CMakeFiles/ContinuousSubmit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ext/pugixml/CMakeFiles/ContinuousSubmit.dir/depend
