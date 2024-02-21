cmake_minimum_required(VERSION 3.27)
project(adventOfCode17)

set(CMAKE_CXX_STANDARD 23)

add_executable(adventOfCode17 main.cpp
        day02/day02.cpp
        day02/day02.h
        day01/day01.cpp
        day01/day01.h
        Day.cpp
        Day.h)
