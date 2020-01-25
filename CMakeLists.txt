cmake_minimum_required(VERSION 3.15)
project(CSGORec)

set(CMAKE_CXX_STANDARD 20)

add_executable(CSGORec main.cpp ConsoleService.cpp ConsoleService.h)

target_link_libraries(CSGORec X11)