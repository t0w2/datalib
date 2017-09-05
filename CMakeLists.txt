cmake_minimum_required(VERSION 2.8.2)
project(datalib C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)

SET(CMAKE_CXX_FLAGS_DEBUG="-Wall -fprofile-arcs -ftest-coverage")

add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(test)

#add_custom_command(TARGET test
#                  POST_BUILD
#                  COMMAND ${CMAKE_BINARY_DIR}/data_test)


