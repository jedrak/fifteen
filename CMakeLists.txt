cmake_minimum_required(VERSION 3.15)
project(fifthteen)

set(CMAKE_CXX_STANDARD 14)

add_executable(fifthteen src/main.cpp src/Puzzle.cpp src/Node.cpp include/Puzzle.h include/Node.h include/Strategy.h src/Graph.cpp include/Graph.h src/BFS.cpp include/BFS.h src/Strategy.cpp src/DFS.cpp include/DFS.h src/Astar.cpp include/Astar.h)