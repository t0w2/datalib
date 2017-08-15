cmake_minimum_required(VERSION 2.8.2)


file(GLOB libs_src "*.h" "*.cpp")
add_library(structurelib ${libs_src})