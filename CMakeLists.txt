cmake_minimum_required(VERSION 3.1)
project(ComputerArchitecture4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp)
add_executable(ComputerArchitecture4 ${SOURCE_FILES} myThread.cpp)