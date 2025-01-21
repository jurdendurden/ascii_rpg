#!/usr/bin/env python3
import os
import glob
import sys
import time
from typing import Tuple, List

#clears terminal
def clear_screen():
    """Clear the terminal screen for different operating systems"""
    os.system('cls' if os.name == 'nt' else 'clear')

#menu header
def print_header():
    """Print the program header"""
    print("=" * 60)
    print("Build System Generator".center(60))
    print("=" * 60)
    print()

def get_source_files() -> Tuple[List[str], List[str]]:
    # Find all C and header files in current directory and subdirectories
    c_files = glob.glob("**/*.c", recursive=True)
    h_files = glob.glob("**/*.h", recursive=True)
    
    # remove any files from subdirectories that start with 'obj/'
    c_files = [f for f in c_files if not f.startswith('obj/')]
    h_files = [f for f in h_files if not f.startswith('obj/')]
    
    return c_files, h_files

def generate_traditional_makefile(target_name: str):
    """Generate a traditional Makefile"""
    makefile_content = """# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -I.

# Get all source files
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,obj/%.o,$(SRC))

# Main target
TARGET = {target}

# Default rule
all: obj $(TARGET)

# Create obj directory
obj:
	mkdir -p obj

# Link rule
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile rule
obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf obj $(TARGET)

# Dependencies
-include $(OBJ:.o=.d)

# Generate dependencies
obj/%.d: %.c
	@set -e; rm -f $@; \\
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \\
	sed 's,\\($*\\)\\.o[ :]*,obj/\\1.o $@ : ,g' < $@.$$$$ > $@; \\
	rm -f $@.$$$$

.PHONY: all clean obj
""".format(target=target_name)

    with open('Makefile', 'w') as f:
        f.write(makefile_content)
    
    if not os.path.exists('obj'):
        os.makedirs('obj')

def generate_cmake(target_name: str, c_files: List[str], h_files: List[str]):
    """Generate CMakeLists.txt"""
    c_files_str = ' '.join(c_files)
    
    cmake_content = """cmake_minimum_required(VERSION 3.10)

# Set project name and language
project({target} C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set compiler flags
add_compile_options(-Wall -Wextra)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${{CMAKE_BINARY_DIR}}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${{CMAKE_BINARY_DIR}}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${{CMAKE_BINARY_DIR}}/lib)

# Create list of source files
set(SOURCES
    {sources}
)

# Create executable target
add_executable(${{PROJECT_NAME}} ${{SOURCES}})

# Add include directories
target_include_directories(${{PROJECT_NAME}} PRIVATE
    ${{CMAKE_CURRENT_SOURCE_DIR}}
)

# Install rules
install(TARGETS ${{PROJECT_NAME}}
    RUNTIME DESTINATION bin
)
""".format(target=target_name, sources=c_files_str)

    with open('CMakeLists.txt', 'w') as f:
        f.write(cmake_content)

def show_file_summary(c_files: List[str], h_files: List[str]):
    """Display summary of found source files"""
    print("\nSource Files Found:")
    print("-" * 40)
    print(f"C Files ({len(c_files)}):")
    for f in c_files:
        print(f"  - {f}")
    print(f"\nHeader Files ({len(h_files)}):")
    for f in h_files:
        print(f"  - {f}")
    print("\nPress Enter to continue...")
    input()

def get_target_name() -> str:
    """Get target name from user"""
    default_name = os.path.basename(os.getcwd())
    while True:
        print(f"\nEnter target name [default: {default_name}]: ", end='')
        name = input().strip()
        if not name:
            return default_name
        if name.isalnum() or '_' in name:
            return name
        print("Invalid name! Use only alphanumeric characters and underscores.")

def get_dir_name() -> str:    
    default_name = "new_c_project"
    while True:
        print(f"\nEnter new project name [default: {default_name}]: ", end='')
        name = input().strip()
        if not name:
            return default_name
        if name.isalnum() or '_' in name:
            return name
        print("Invalid name! Use only alphanumeric characters and underscores.")

def show_success_message(build_type: str, target_name: str):
    #show success message with build instructions
    print("\nSuccess! Build files generated successfully.")
    print(f"Target name: {target_name}")
    
    if build_type == 'cmake':
        print("\nTo build with CMake:")
        print("1. mkdir build")
        print("2. cd build")
        print("3. cmake ..")
        print("4. make")
    else:
        print("\nTo build with Make:")
        print("1. make")
        print("\nTo clean (aka recompile with headers):")
        print("make clean")
    
    print("\nPress Enter to return to main menu...")
    input()

def main_menu():
    """Display and handle the main menu"""
    while True:
        clear_screen()
        print_header()
        
        c_files, h_files = get_source_files()
        
        print("Main Menu:")
        print("1. Show source files summary")
        print("2. Generate GCC Makefile")
        print("3. Generate CMake build")
        print("4. Exit")
        print("\nChoice: ", end='')
        
        choice = input().strip()
        
        if not c_files and choice in ['2', '3']:
            print("\nError: No .c files found in the current directory!")
            print("Press Enter to continue...")
            input()
            continue
        
        if choice == '1':
            show_file_summary(c_files, h_files)
        elif choice == '2':
            target_name = get_target_name()
            generate_traditional_makefile(target_name)
            show_success_message('make', target_name)
        elif choice == '3':
            target_name = get_target_name()
            generate_cmake(target_name, c_files, h_files)
            show_success_message('cmake', target_name)
        elif choice == '4':
            clear_screen()
            print("Thank you for using maker!")
            sys.exit(0)
        else:
            print("\nInvalid choice! Press Enter to try again...")
            input()

if __name__ == "__main__":
    try:
        main_menu()
    except KeyboardInterrupt:
        print("\nProgram interrupted by user. Exiting...")
        sys.exit(1)