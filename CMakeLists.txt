cmake_minimum_required(VERSION 2.8.2)
project(datastructures C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)


add_subdirectory(src)
add_subdirectory(libs)
add_subdirectory(test)


