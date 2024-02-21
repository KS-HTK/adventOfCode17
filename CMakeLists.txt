cmake_minimum_required(VERSION 3.27)
project(adventOfCode17)

set(CMAKE_CXX_STANDARD 23)

add_executable(adventOfCode17 main.cpp
        Day.h
        Day.cpp
        day01/day01.h
        day01/day01.cpp
        day02/day02.h
        day02/day02.cpp
        day03/day03.h
        day03/day03.cpp)
