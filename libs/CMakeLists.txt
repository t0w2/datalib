cmake_minimum_required(VERSION 2.8.2)
project(libs C CXX)

SET(CMAKE_CXX_FLAGS_DEBUG="-Wall -fprofile-arcs -ftest-coverage")

file(GLOB libs_src "*.h" "*.cpp")
add_library(libs ${libs_src})

export(TARGETS libs FILE libs.cmake)