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
CMAKE_SOURCE_DIR = /home/uos/Documents/github/examples/graphic-driver/gltest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/uos/Documents/github/examples/graphic-driver/gltest/buid

# Include any dependencies generated for this target.
include CMakeFiles/gltest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gltest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gltest.dir/flags.make

CMakeFiles/gltest.dir/gltestwidget.cpp.o: CMakeFiles/gltest.dir/flags.make
CMakeFiles/gltest.dir/gltestwidget.cpp.o: ../gltestwidget.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/uos/Documents/github/examples/graphic-driver/gltest/buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gltest.dir/gltestwidget.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gltest.dir/gltestwidget.cpp.o -c /home/uos/Documents/github/examples/graphic-driver/gltest/gltestwidget.cpp

CMakeFiles/gltest.dir/gltestwidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gltest.dir/gltestwidget.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/uos/Documents/github/examples/graphic-driver/gltest/gltestwidget.cpp > CMakeFiles/gltest.dir/gltestwidget.cpp.i

CMakeFiles/gltest.dir/gltestwidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gltest.dir/gltestwidget.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/uos/Documents/github/examples/graphic-driver/gltest/gltestwidget.cpp -o CMakeFiles/gltest.dir/gltestwidget.cpp.s

CMakeFiles/gltest.dir/gltestwindow.cpp.o: CMakeFiles/gltest.dir/flags.make
CMakeFiles/gltest.dir/gltestwindow.cpp.o: ../gltestwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/uos/Documents/github/examples/graphic-driver/gltest/buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gltest.dir/gltestwindow.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gltest.dir/gltestwindow.cpp.o -c /home/uos/Documents/github/examples/graphic-driver/gltest/gltestwindow.cpp

CMakeFiles/gltest.dir/gltestwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gltest.dir/gltestwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/uos/Documents/github/examples/graphic-driver/gltest/gltestwindow.cpp > CMakeFiles/gltest.dir/gltestwindow.cpp.i

CMakeFiles/gltest.dir/gltestwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gltest.dir/gltestwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/uos/Documents/github/examples/graphic-driver/gltest/gltestwindow.cpp -o CMakeFiles/gltest.dir/gltestwindow.cpp.s

CMakeFiles/gltest.dir/main.cpp.o: CMakeFiles/gltest.dir/flags.make
CMakeFiles/gltest.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/uos/Documents/github/examples/graphic-driver/gltest/buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/gltest.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gltest.dir/main.cpp.o -c /home/uos/Documents/github/examples/graphic-driver/gltest/main.cpp

CMakeFiles/gltest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gltest.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/uos/Documents/github/examples/graphic-driver/gltest/main.cpp > CMakeFiles/gltest.dir/main.cpp.i

CMakeFiles/gltest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gltest.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/uos/Documents/github/examples/graphic-driver/gltest/main.cpp -o CMakeFiles/gltest.dir/main.cpp.s

CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.o: CMakeFiles/gltest.dir/flags.make
CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.o: gltest_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/uos/Documents/github/examples/graphic-driver/gltest/buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.o -c /home/uos/Documents/github/examples/graphic-driver/gltest/buid/gltest_autogen/mocs_compilation.cpp

CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/uos/Documents/github/examples/graphic-driver/gltest/buid/gltest_autogen/mocs_compilation.cpp > CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.i

CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/uos/Documents/github/examples/graphic-driver/gltest/buid/gltest_autogen/mocs_compilation.cpp -o CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.s

# Object files for target gltest
gltest_OBJECTS = \
"CMakeFiles/gltest.dir/gltestwidget.cpp.o" \
"CMakeFiles/gltest.dir/gltestwindow.cpp.o" \
"CMakeFiles/gltest.dir/main.cpp.o" \
"CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.o"

# External object files for target gltest
gltest_EXTERNAL_OBJECTS =

gltest: CMakeFiles/gltest.dir/gltestwidget.cpp.o
gltest: CMakeFiles/gltest.dir/gltestwindow.cpp.o
gltest: CMakeFiles/gltest.dir/main.cpp.o
gltest: CMakeFiles/gltest.dir/gltest_autogen/mocs_compilation.cpp.o
gltest: CMakeFiles/gltest.dir/build.make
gltest: /usr/lib/x86_64-linux-gnu/libGL.so
gltest: /usr/lib/x86_64-linux-gnu/libGLU.so
gltest: /usr/lib/x86_64-linux-gnu/libglut.so
gltest: /usr/lib/x86_64-linux-gnu/libXmu.so
gltest: /usr/lib/x86_64-linux-gnu/libXi.so
gltest: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.11.3
gltest: /usr/lib/x86_64-linux-gnu/libQt5DBus.so.5.11.3
gltest: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.11.3
gltest: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.11.3
gltest: CMakeFiles/gltest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/uos/Documents/github/examples/graphic-driver/gltest/buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable gltest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gltest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gltest.dir/build: gltest

.PHONY : CMakeFiles/gltest.dir/build

CMakeFiles/gltest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gltest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gltest.dir/clean

CMakeFiles/gltest.dir/depend:
	cd /home/uos/Documents/github/examples/graphic-driver/gltest/buid && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/uos/Documents/github/examples/graphic-driver/gltest /home/uos/Documents/github/examples/graphic-driver/gltest /home/uos/Documents/github/examples/graphic-driver/gltest/buid /home/uos/Documents/github/examples/graphic-driver/gltest/buid /home/uos/Documents/github/examples/graphic-driver/gltest/buid/CMakeFiles/gltest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gltest.dir/depend

