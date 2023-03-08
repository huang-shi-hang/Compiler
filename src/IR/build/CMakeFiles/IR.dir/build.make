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
CMAKE_SOURCE_DIR = /root/compiler/AAA/IR

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/compiler/AAA/IR/build

# Include any dependencies generated for this target.
include CMakeFiles/IR.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IR.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IR.dir/flags.make

hshparser.tab.cpp: ../hshparser.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/compiler/AAA/IR/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating hshparser.tab.cpp, hshparser.tab.hpp"
	bison -d -o hshparser.tab.cpp --defines=hshparser.tab.hpp ../hshparser.y

hshparser.tab.hpp: hshparser.tab.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate hshparser.tab.hpp

hshlex.yy.cpp: ../hshlex.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/compiler/AAA/IR/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating hshlex.yy.cpp, hshlex.yy.hpp"
	flex -o hshlex.yy.cpp --header=hshlex.yy.hpp ../hshlex.l

hshlex.yy.hpp: hshlex.yy.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate hshlex.yy.hpp

CMakeFiles/IR.dir/types.cpp.o: CMakeFiles/IR.dir/flags.make
CMakeFiles/IR.dir/types.cpp.o: ../types.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/compiler/AAA/IR/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/IR.dir/types.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR.dir/types.cpp.o -c /root/compiler/AAA/IR/types.cpp

CMakeFiles/IR.dir/types.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR.dir/types.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/compiler/AAA/IR/types.cpp > CMakeFiles/IR.dir/types.cpp.i

CMakeFiles/IR.dir/types.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR.dir/types.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/compiler/AAA/IR/types.cpp -o CMakeFiles/IR.dir/types.cpp.s

CMakeFiles/IR.dir/hshparser.tab.cpp.o: CMakeFiles/IR.dir/flags.make
CMakeFiles/IR.dir/hshparser.tab.cpp.o: hshparser.tab.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/compiler/AAA/IR/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/IR.dir/hshparser.tab.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR.dir/hshparser.tab.cpp.o -c /root/compiler/AAA/IR/build/hshparser.tab.cpp

CMakeFiles/IR.dir/hshparser.tab.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR.dir/hshparser.tab.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/compiler/AAA/IR/build/hshparser.tab.cpp > CMakeFiles/IR.dir/hshparser.tab.cpp.i

CMakeFiles/IR.dir/hshparser.tab.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR.dir/hshparser.tab.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/compiler/AAA/IR/build/hshparser.tab.cpp -o CMakeFiles/IR.dir/hshparser.tab.cpp.s

CMakeFiles/IR.dir/hshlex.yy.cpp.o: CMakeFiles/IR.dir/flags.make
CMakeFiles/IR.dir/hshlex.yy.cpp.o: hshlex.yy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/compiler/AAA/IR/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/IR.dir/hshlex.yy.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR.dir/hshlex.yy.cpp.o -c /root/compiler/AAA/IR/build/hshlex.yy.cpp

CMakeFiles/IR.dir/hshlex.yy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR.dir/hshlex.yy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/compiler/AAA/IR/build/hshlex.yy.cpp > CMakeFiles/IR.dir/hshlex.yy.cpp.i

CMakeFiles/IR.dir/hshlex.yy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR.dir/hshlex.yy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/compiler/AAA/IR/build/hshlex.yy.cpp -o CMakeFiles/IR.dir/hshlex.yy.cpp.s

# Object files for target IR
IR_OBJECTS = \
"CMakeFiles/IR.dir/types.cpp.o" \
"CMakeFiles/IR.dir/hshparser.tab.cpp.o" \
"CMakeFiles/IR.dir/hshlex.yy.cpp.o"

# External object files for target IR
IR_EXTERNAL_OBJECTS =

IR: CMakeFiles/IR.dir/types.cpp.o
IR: CMakeFiles/IR.dir/hshparser.tab.cpp.o
IR: CMakeFiles/IR.dir/hshlex.yy.cpp.o
IR: CMakeFiles/IR.dir/build.make
IR: CMakeFiles/IR.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/compiler/AAA/IR/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable IR"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IR.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IR.dir/build: IR

.PHONY : CMakeFiles/IR.dir/build

CMakeFiles/IR.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IR.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IR.dir/clean

CMakeFiles/IR.dir/depend: hshparser.tab.cpp
CMakeFiles/IR.dir/depend: hshparser.tab.hpp
CMakeFiles/IR.dir/depend: hshlex.yy.cpp
CMakeFiles/IR.dir/depend: hshlex.yy.hpp
	cd /root/compiler/AAA/IR/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/compiler/AAA/IR /root/compiler/AAA/IR /root/compiler/AAA/IR/build /root/compiler/AAA/IR/build /root/compiler/AAA/IR/build/CMakeFiles/IR.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IR.dir/depend
