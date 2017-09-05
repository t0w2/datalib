cmake_minimum_required(VERSION 2.8.2)
project(datastruct C CXX)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)

set (CMAKE_CXX_FLAGS_DEBUG "-Wall -fprofile-arcs -ftest-coverage")
file(GLOB data_src "*.h" "*.cpp")
add_executable(datastruct ${data_src})
target_link_libraries(datastruct libs)
