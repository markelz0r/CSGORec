cmake_minimum_required(VERSION 3.15)
project(CSGORec)

set(CMAKE_CXX_STANDARD 20)

add_executable(CSGORec main.cpp Services/ConsoleService.cpp Services/ConsoleService.h Services/BashService.cpp Services/BashService.h Services/GameService.cpp Services/GameService.h)

target_link_libraries(CSGORec X11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")