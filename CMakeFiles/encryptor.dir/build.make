# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maverick/Documents/Proyecto/C++/EncryptorProyect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maverick/Documents/Proyecto/C++/EncryptorProyect

# Include any dependencies generated for this target.
include CMakeFiles/encryptor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/encryptor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/encryptor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/encryptor.dir/flags.make

CMakeFiles/encryptor.dir/src/main.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/encryptor.dir/src/main.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/encryptor.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/main.cpp.o -MF CMakeFiles/encryptor.dir/src/main.cpp.o.d -o CMakeFiles/encryptor.dir/src/main.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/main.cpp

CMakeFiles/encryptor.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/main.cpp > CMakeFiles/encryptor.dir/src/main.cpp.i

CMakeFiles/encryptor.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/main.cpp -o CMakeFiles/encryptor.dir/src/main.cpp.s

CMakeFiles/encryptor.dir/src/encryption.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/encryption.cpp.o: src/encryption.cpp
CMakeFiles/encryptor.dir/src/encryption.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/encryptor.dir/src/encryption.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/encryption.cpp.o -MF CMakeFiles/encryptor.dir/src/encryption.cpp.o.d -o CMakeFiles/encryptor.dir/src/encryption.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/encryption.cpp

CMakeFiles/encryptor.dir/src/encryption.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/encryption.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/encryption.cpp > CMakeFiles/encryptor.dir/src/encryption.cpp.i

CMakeFiles/encryptor.dir/src/encryption.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/encryption.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/encryption.cpp -o CMakeFiles/encryptor.dir/src/encryption.cpp.s

CMakeFiles/encryptor.dir/src/file_utils.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/file_utils.cpp.o: src/file_utils.cpp
CMakeFiles/encryptor.dir/src/file_utils.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/encryptor.dir/src/file_utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/file_utils.cpp.o -MF CMakeFiles/encryptor.dir/src/file_utils.cpp.o.d -o CMakeFiles/encryptor.dir/src/file_utils.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/file_utils.cpp

CMakeFiles/encryptor.dir/src/file_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/file_utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/file_utils.cpp > CMakeFiles/encryptor.dir/src/file_utils.cpp.i

CMakeFiles/encryptor.dir/src/file_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/file_utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/file_utils.cpp -o CMakeFiles/encryptor.dir/src/file_utils.cpp.s

CMakeFiles/encryptor.dir/src/key_derivation.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/key_derivation.cpp.o: src/key_derivation.cpp
CMakeFiles/encryptor.dir/src/key_derivation.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/encryptor.dir/src/key_derivation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/key_derivation.cpp.o -MF CMakeFiles/encryptor.dir/src/key_derivation.cpp.o.d -o CMakeFiles/encryptor.dir/src/key_derivation.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/key_derivation.cpp

CMakeFiles/encryptor.dir/src/key_derivation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/key_derivation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/key_derivation.cpp > CMakeFiles/encryptor.dir/src/key_derivation.cpp.i

CMakeFiles/encryptor.dir/src/key_derivation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/key_derivation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/key_derivation.cpp -o CMakeFiles/encryptor.dir/src/key_derivation.cpp.s

CMakeFiles/encryptor.dir/src/openssl_utils.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/openssl_utils.cpp.o: src/openssl_utils.cpp
CMakeFiles/encryptor.dir/src/openssl_utils.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/encryptor.dir/src/openssl_utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/openssl_utils.cpp.o -MF CMakeFiles/encryptor.dir/src/openssl_utils.cpp.o.d -o CMakeFiles/encryptor.dir/src/openssl_utils.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/openssl_utils.cpp

CMakeFiles/encryptor.dir/src/openssl_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/openssl_utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/openssl_utils.cpp > CMakeFiles/encryptor.dir/src/openssl_utils.cpp.i

CMakeFiles/encryptor.dir/src/openssl_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/openssl_utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/openssl_utils.cpp -o CMakeFiles/encryptor.dir/src/openssl_utils.cpp.s

CMakeFiles/encryptor.dir/src/mysql_utils.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/mysql_utils.cpp.o: src/mysql_utils.cpp
CMakeFiles/encryptor.dir/src/mysql_utils.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/encryptor.dir/src/mysql_utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/mysql_utils.cpp.o -MF CMakeFiles/encryptor.dir/src/mysql_utils.cpp.o.d -o CMakeFiles/encryptor.dir/src/mysql_utils.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/mysql_utils.cpp

CMakeFiles/encryptor.dir/src/mysql_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/mysql_utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/mysql_utils.cpp > CMakeFiles/encryptor.dir/src/mysql_utils.cpp.i

CMakeFiles/encryptor.dir/src/mysql_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/mysql_utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/mysql_utils.cpp -o CMakeFiles/encryptor.dir/src/mysql_utils.cpp.s

CMakeFiles/encryptor.dir/src/colors.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/colors.cpp.o: src/colors.cpp
CMakeFiles/encryptor.dir/src/colors.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/encryptor.dir/src/colors.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/colors.cpp.o -MF CMakeFiles/encryptor.dir/src/colors.cpp.o.d -o CMakeFiles/encryptor.dir/src/colors.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/colors.cpp

CMakeFiles/encryptor.dir/src/colors.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/colors.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/colors.cpp > CMakeFiles/encryptor.dir/src/colors.cpp.i

CMakeFiles/encryptor.dir/src/colors.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/colors.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/colors.cpp -o CMakeFiles/encryptor.dir/src/colors.cpp.s

CMakeFiles/encryptor.dir/src/directories.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/directories.cpp.o: src/directories.cpp
CMakeFiles/encryptor.dir/src/directories.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/encryptor.dir/src/directories.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/directories.cpp.o -MF CMakeFiles/encryptor.dir/src/directories.cpp.o.d -o CMakeFiles/encryptor.dir/src/directories.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/directories.cpp

CMakeFiles/encryptor.dir/src/directories.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/directories.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/directories.cpp > CMakeFiles/encryptor.dir/src/directories.cpp.i

CMakeFiles/encryptor.dir/src/directories.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/directories.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/directories.cpp -o CMakeFiles/encryptor.dir/src/directories.cpp.s

CMakeFiles/encryptor.dir/src/password_prompt.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/password_prompt.cpp.o: src/password_prompt.cpp
CMakeFiles/encryptor.dir/src/password_prompt.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/encryptor.dir/src/password_prompt.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/password_prompt.cpp.o -MF CMakeFiles/encryptor.dir/src/password_prompt.cpp.o.d -o CMakeFiles/encryptor.dir/src/password_prompt.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/password_prompt.cpp

CMakeFiles/encryptor.dir/src/password_prompt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/password_prompt.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/password_prompt.cpp > CMakeFiles/encryptor.dir/src/password_prompt.cpp.i

CMakeFiles/encryptor.dir/src/password_prompt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/password_prompt.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/password_prompt.cpp -o CMakeFiles/encryptor.dir/src/password_prompt.cpp.s

CMakeFiles/encryptor.dir/src/time_utils.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/time_utils.cpp.o: src/time_utils.cpp
CMakeFiles/encryptor.dir/src/time_utils.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/encryptor.dir/src/time_utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/time_utils.cpp.o -MF CMakeFiles/encryptor.dir/src/time_utils.cpp.o.d -o CMakeFiles/encryptor.dir/src/time_utils.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/time_utils.cpp

CMakeFiles/encryptor.dir/src/time_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/time_utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/time_utils.cpp > CMakeFiles/encryptor.dir/src/time_utils.cpp.i

CMakeFiles/encryptor.dir/src/time_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/time_utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/time_utils.cpp -o CMakeFiles/encryptor.dir/src/time_utils.cpp.s

CMakeFiles/encryptor.dir/src/menu.cpp.o: CMakeFiles/encryptor.dir/flags.make
CMakeFiles/encryptor.dir/src/menu.cpp.o: src/menu.cpp
CMakeFiles/encryptor.dir/src/menu.cpp.o: CMakeFiles/encryptor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/encryptor.dir/src/menu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encryptor.dir/src/menu.cpp.o -MF CMakeFiles/encryptor.dir/src/menu.cpp.o.d -o CMakeFiles/encryptor.dir/src/menu.cpp.o -c /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/menu.cpp

CMakeFiles/encryptor.dir/src/menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encryptor.dir/src/menu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/menu.cpp > CMakeFiles/encryptor.dir/src/menu.cpp.i

CMakeFiles/encryptor.dir/src/menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encryptor.dir/src/menu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maverick/Documents/Proyecto/C++/EncryptorProyect/src/menu.cpp -o CMakeFiles/encryptor.dir/src/menu.cpp.s

# Object files for target encryptor
encryptor_OBJECTS = \
"CMakeFiles/encryptor.dir/src/main.cpp.o" \
"CMakeFiles/encryptor.dir/src/encryption.cpp.o" \
"CMakeFiles/encryptor.dir/src/file_utils.cpp.o" \
"CMakeFiles/encryptor.dir/src/key_derivation.cpp.o" \
"CMakeFiles/encryptor.dir/src/openssl_utils.cpp.o" \
"CMakeFiles/encryptor.dir/src/mysql_utils.cpp.o" \
"CMakeFiles/encryptor.dir/src/colors.cpp.o" \
"CMakeFiles/encryptor.dir/src/directories.cpp.o" \
"CMakeFiles/encryptor.dir/src/password_prompt.cpp.o" \
"CMakeFiles/encryptor.dir/src/time_utils.cpp.o" \
"CMakeFiles/encryptor.dir/src/menu.cpp.o"

# External object files for target encryptor
encryptor_EXTERNAL_OBJECTS =

encryptor: CMakeFiles/encryptor.dir/src/main.cpp.o
encryptor: CMakeFiles/encryptor.dir/src/encryption.cpp.o
encryptor: CMakeFiles/encryptor.dir/src/file_utils.cpp.o
encryptor: CMakeFiles/encryptor.dir/src/key_derivation.cpp.o
encryptor: CMakeFiles/encryptor.dir/src/openssl_utils.cpp.o
encryptor: CMakeFiles/encryptor.dir/src/mysql_utils.cpp.o
encryptor: CMakeFiles/encryptor.dir/src/colors.cpp.o
encryptor: CMakeFiles/encryptor.dir/src/directories.cpp.o
encryptor: CMakeFiles/encryptor.dir/src/password_prompt.cpp.o
encryptor: CMakeFiles/encryptor.dir/src/time_utils.cpp.o
encryptor: CMakeFiles/encryptor.dir/src/menu.cpp.o
encryptor: CMakeFiles/encryptor.dir/build.make
encryptor: /usr/lib/x86_64-linux-gnu/libssl.so
encryptor: /usr/lib/x86_64-linux-gnu/libcrypto.so
encryptor: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
encryptor: /usr/lib/x86_64-linux-gnu/libcurses.so
encryptor: /usr/lib/x86_64-linux-gnu/libform.so
encryptor: CMakeFiles/encryptor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable encryptor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/encryptor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/encryptor.dir/build: encryptor
.PHONY : CMakeFiles/encryptor.dir/build

CMakeFiles/encryptor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/encryptor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/encryptor.dir/clean

CMakeFiles/encryptor.dir/depend:
	cd /home/maverick/Documents/Proyecto/C++/EncryptorProyect && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maverick/Documents/Proyecto/C++/EncryptorProyect /home/maverick/Documents/Proyecto/C++/EncryptorProyect /home/maverick/Documents/Proyecto/C++/EncryptorProyect /home/maverick/Documents/Proyecto/C++/EncryptorProyect /home/maverick/Documents/Proyecto/C++/EncryptorProyect/CMakeFiles/encryptor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/encryptor.dir/depend

