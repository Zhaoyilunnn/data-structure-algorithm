cmake_minimum_required(VERSION 3.15)
project(data_structure_learn)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(data_structure_learn
        main.cpp
        tree.cpp
        tree.h graph.cpp graph.h common.h sort.h sort.cpp algorithm.h algorithm.cpp)
