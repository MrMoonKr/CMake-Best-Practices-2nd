
# CMakeLists file for the Chapter 1 example illustrating how to create a simple executable
# 
# SPDX-License-Identifier: MIT

cmake_minimum_required( VERSION 3.23 )

set(VCPKG_TARGET_TRIPLET "x64-mingw-static" CACHE STRING "")
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Define a CMake project
project(
    ch1_simple_executable
    VERSION 1.0
    DESCRIPTION "A simple C++ project to demonstrate basic CMake usage"
    LANGUAGES CXX
)

find_package( fmt CONFIG REQUIRED )

# Add an executable target named `chapter1`
add_executable( ch1_simple_executable )
# Add sources to the target `chapter1`
target_sources( ch1_simple_executable PRIVATE src/main.cpp )

target_link_libraries( ch1_simple_executable PRIVATE fmt::fmt )