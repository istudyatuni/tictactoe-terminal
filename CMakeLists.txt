cmake_minimum_required (VERSION 2.8)

project(TicTacToe)
include_directories("include")

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Os")
set(CMAKE_CXX_FLAGS_RELEASE "-w -Os")

set(SOURCE src/main.cpp src/map.cpp src/tictactoe.cpp)

add_executable(game ${SOURCE})