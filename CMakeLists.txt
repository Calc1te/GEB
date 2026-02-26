cmake_minimum_required(VERSION 3.31)
project(GEB)

set(CMAKE_CXX_STANDARD 20)

add_executable(GEB main.cpp
        WJUProblem.cpp
        WJUProblem.h
        DFS.cpp
        DFS.h
        BFS.cpp
        BFS.h)
