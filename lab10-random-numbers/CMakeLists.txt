cmake_minimum_required(VERSION 4.0)
project(lab10_random_numbers)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(lab10_random_numbers
        main.cpp
        RandGen_2.cpp)
