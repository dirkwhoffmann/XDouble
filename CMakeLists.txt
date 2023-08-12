cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
  double-double
  VERSION 0.0.1
  DESCRIPTION "A lightweight double-double arithmetic library in C++"
  HOMEPAGE_URL "https://www.dirkwhoffmann.de"
  LANGUAGES CXX C)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

# Set the optimization level (if not specified on the command line)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Add the core library
add_library(doubledouble double-double.cpp)

# Specify compile options
if(MSVC)
  target_compile_options(doubledouble PUBLIC /W4)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(doubledouble PUBLIC -Wall -Werror)
endif()

# Add the unit tester
add_subdirectory(unittests)
