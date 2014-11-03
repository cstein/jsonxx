cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(jsonxx)

option(BUILD_TEST "Build test samples" OFF)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder")

add_library(jsonxx
    jsonxx.cc)

if(BUILD_TEST)
    add_executable(jsonxx_test
                   jsonxx_test.cc)

target_link_libraries(jsonxx_test
    jsonxx)

endif(BUILD_TEST)
