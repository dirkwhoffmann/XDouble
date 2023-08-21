cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
  xdouble
  VERSION 0.9
  DESCRIPTION "A header-only double-double arithmetic library written in C++"
  HOMEPAGE_URL "https://www.dirkwhoffmann.de"
  LANGUAGES CXX C)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

# Set the optimization level (if not specified on the command line)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(unittests)

add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)
