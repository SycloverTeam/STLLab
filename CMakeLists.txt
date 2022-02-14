cmake_minimum_required(VERSION 3.20)

project(TINYSTL)

set(TINYSTL_VERSION_MAJOR 0)
set(TINYSTL_VERSION_MINOR 1)
set(TINYSTL_VERSION_PATCH 0)
set(TINYSTL_VERSION "${TINYSTL_VERSION_MAJOR}.${TINYSTL_VERSION_MINOR}.${TINYSTL_VERSION_PATCH}")
message(STATUS "The version of this project is ${TINYSTL_VERSION}")

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall ")
set(CMAKE_CXX_STANDARD 11)

message(STATUS "the cmake_cxx_flags ${CMAKE_CXX_FLAGS}")

include_directories(${PROJECT_SOURCE_DIR}/src)

set(TEST test/cppunit/test_main.cpp)
#file(GLOB_RECURSE TEST_FILE "test/*.cpp") # open the all test file
#set(TEST_FILE test/memory_test.cpp) # open one test file

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(stltest ${TEST} ${TEST_FILE})