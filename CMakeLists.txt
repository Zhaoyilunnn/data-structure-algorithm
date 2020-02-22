cmake_minimum_required(VERSION 3.15)
project(data_structure_learn)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(data_structure_learn
        main.cpp
        struc_func.cpp
        struc_func.hpp)
