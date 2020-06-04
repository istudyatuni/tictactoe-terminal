cmake_minimum_required (VERSION 2.8)

project(TicTacToe)
include_directories("include")

set(CMAKE_CXX_FLAGS "-Wall")

add_executable(game src/main.cpp src/map.cpp)