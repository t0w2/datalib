cmake_minimum_required(VERSION 2.8.2)

project(datatesting)
enable_testing()

include(Dart)

# Download and unpack googletest at configure time
message(${CMAKE_CURRENT_BINARY_DIR})
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()


# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
file(GLOB test_src "*.h" "*.cpp")
add_executable(data_test ${test_src})
target_link_libraries(data_test gtest_main)

add_custom_command(TARGET data_test
                  POST_BUILD
                  COMMAND ${CMAKE_BINARY_DIR}/data_test)
#[[
add_test(NAME data_test 
        COMMAND ${CMAKE_BINARY_DIR}/data_test)
add_test(own_hash.constructor1 
        ${CMAKE_BINARY_DIR}/data_test)
]]