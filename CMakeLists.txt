cmake_minimum_required(VERSION 3.16)
project(gogameserver)

set(CMAKE_CXX_STANDARD 14)

add_executable(gogameserver main.cpp Header/Pawn.h Sources/Pawn.cpp Header/Player.h Sources/Player.cpp Header/Board.h Sources/Board.cpp)