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

add_executable(unittester

    main.cpp
    smoke_tests.cpp
    constant_tests.cpp
    arithmetic_tests.cpp
    comparison_tests.cpp
    explog_tests.cpp
    power_tests.cpp
    rounding_tests.cpp
    manipulation_tests.cpp
    minmax_tests.cpp
    other_tests.cpp
    classification_tests.cpp
    quaddouble_tests.cpp
)

# Specify compile options
target_compile_options(unittester PUBLIC -Wall -Werror -Wno-unknown-pragmas)
if(MSVC)
  target_compile_options(unittester PUBLIC /W4)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
endif()

enable_testing()

target_include_directories(unittester PRIVATE ${CMAKE_SOURCE_DIR}/..)
add_test(xdouble unittester)
