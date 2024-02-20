cmake_minimum_required(VERSION 3.27)
project(adventOfCode17)

set(CMAKE_CXX_STANDARD 23)

add_executable(adventOfCode17 main.cpp
        day01/day01.cpp
        day01/day01.h
        day01/Day.cpp
        day01/Day.h)
