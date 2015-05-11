cmake_minimum_required(VERSION 3.1)
project(ComputerArchitecture4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -lboost_serialization -lboost_program_options")

set(SOURCE_FILES server.cpp)
add_executable(ComputerArchitecture4 ${SOURCE_FILES} thread/myThread.h thread/myThread.cpp programmer/Programmer.cpp programmer/Programmer.h socket/TCPSocket.cpp socket/TCPSocket.h connection/connection.h)