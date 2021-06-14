cmake_minimum_required(VERSION 3.17)
project(pathFinding)

set(CMAKE_CXX_STANDARD 14)

add_executable(pathFinding main.cpp Node.cpp Node.h Maze.cpp Maze.h MazeGenerator.cpp MazeGenerator.h)