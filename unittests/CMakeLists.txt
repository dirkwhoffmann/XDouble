cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

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

target_include_directories(unittester PRIVATE ${CMAKE_SOURCE_DIR})

# Specify compile options
if(MSVC)
  target_compile_options(unittester PUBLIC /W4)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(unittester PUBLIC -Wall -Werror -Wno-unknown-pragmas)
else()
  target_compile_options(unittester PUBLIC -Wall -Werror -Wno-unknown-pragmas)
endif()

enable_testing()

add_test(xdouble example1)
add_test(xdouble unittester)
