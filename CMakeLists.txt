cmake_minimum_required(VERSION 3.0)
project(CatsVSDogs)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define your source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Include directories
include_directories(include)

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

