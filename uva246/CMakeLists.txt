project(chapterFirstExample)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include)
link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GMOCK_HOME}/gtest/mybuild)
add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -g -Wall")

set(sources 
    uva246.cpp)
add_executable(test ${sources})

target_link_libraries(test gmock)
target_link_libraries(test gtest)
target_link_libraries(test pthread)

