cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# project(tests LANGUAGES CXX)

enable_testing()

add_executable(unittester main.cpp tests.cpp moretests.cpp)
target_include_directories(unittester PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(unittester PRIVATE doubledouble)
add_test(unittest unittester)