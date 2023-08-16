cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# project(tests LANGUAGES CXX)

enable_testing()

add_executable(unittester

    main.cpp
    smoke_tests.cpp
    arithmetic_tests.cpp
    comparison_tests.cpp
    explog_tests.cpp
    power_tests.cpp
    rounding_tests.cpp
    manipulation_tests.cpp
    minmax_tests.cpp
    other_tests.cpp
)
target_include_directories(unittester PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(unittester PRIVATE doubledouble)
add_test(unittest unittester)
