# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build

# Include any dependencies generated for this target.
include CMakeFiles/CPTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CPTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CPTest.dir/flags.make

CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp: ../CPTestPlugin.qrc
CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp: CMakeFiles/CPTest_autogen.dir/RCCCPTestPluginInfo.cmake
CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp: ../Layers.qml
CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp: ../Resources/Layers.png
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic RCC for CPTestPlugin.qrc"
	/usr/local/bin/cmake -E cmake_autorcc /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CMakeFiles/CPTest_autogen.dir/RCCCPTestPluginInfo.cmake Debug

CMakeFiles/CPTest.dir/CPTestPlugin.cpp.o: CMakeFiles/CPTest.dir/flags.make
CMakeFiles/CPTest.dir/CPTestPlugin.cpp.o: ../CPTestPlugin.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CPTest.dir/CPTestPlugin.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CPTest.dir/CPTestPlugin.cpp.o -c /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/CPTestPlugin.cpp

CMakeFiles/CPTest.dir/CPTestPlugin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPTest.dir/CPTestPlugin.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/CPTestPlugin.cpp > CMakeFiles/CPTest.dir/CPTestPlugin.cpp.i

CMakeFiles/CPTest.dir/CPTestPlugin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPTest.dir/CPTestPlugin.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/CPTestPlugin.cpp -o CMakeFiles/CPTest.dir/CPTestPlugin.cpp.s

CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.o: CMakeFiles/CPTest.dir/flags.make
CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.o: CPTest_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.o -c /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CPTest_autogen/mocs_compilation.cpp

CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CPTest_autogen/mocs_compilation.cpp > CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.i

CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CPTest_autogen/mocs_compilation.cpp -o CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.s

CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.o: CMakeFiles/CPTest.dir/flags.make
CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.o: CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.o -c /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp

CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp > CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.i

CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp -o CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.s

# Object files for target CPTest
CPTest_OBJECTS = \
"CMakeFiles/CPTest.dir/CPTestPlugin.cpp.o" \
"CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.o"

# External object files for target CPTest
CPTest_EXTERNAL_OBJECTS =

libCPTest.so: CMakeFiles/CPTest.dir/CPTestPlugin.cpp.o
libCPTest.so: CMakeFiles/CPTest.dir/CPTest_autogen/mocs_compilation.cpp.o
libCPTest.so: CMakeFiles/CPTest.dir/CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp.o
libCPTest.so: CMakeFiles/CPTest.dir/build.make
libCPTest.so: /home/client112/Qt5.13.1/5.13.1/gcc_64/lib/libQt5Quick.so.5.13.1
libCPTest.so: /home/client112/Qt5.13.1/5.13.1/gcc_64/lib/libQt5Gui.so.5.13.1
libCPTest.so: /home/client112/Qt5.13.1/5.13.1/gcc_64/lib/libQt5Qml.so.5.13.1
libCPTest.so: /home/client112/Qt5.13.1/5.13.1/gcc_64/lib/libQt5Network.so.5.13.1
libCPTest.so: /home/client112/Qt5.13.1/5.13.1/gcc_64/lib/libQt5Core.so.5.13.1
libCPTest.so: CMakeFiles/CPTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libCPTest.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CPTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CPTest.dir/build: libCPTest.so

.PHONY : CMakeFiles/CPTest.dir/build

CMakeFiles/CPTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CPTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CPTest.dir/clean

CMakeFiles/CPTest.dir/depend: CPTest_autogen/EWIEGA46WW/qrc_CPTestPlugin.cpp
	cd /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build /home/client112/Documents/mbr/QTMAP3D-SAMPLE/Crystal/CPTest/build/CMakeFiles/CPTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CPTest.dir/depend

