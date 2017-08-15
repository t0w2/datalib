cmake_minimum_required(VERSION 2.8.2)


file(GLOB datastructures_src "*.h" "*.cpp")
add_executable(datastructures ${datastructures_src})