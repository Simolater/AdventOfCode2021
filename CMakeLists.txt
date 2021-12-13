cmake_minimum_required(VERSION 3.20)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 23)

file (GLOB day_src "src/impl/*.cpp")

add_executable(AdventOfCode main.cpp Matrix.h AoC.h src/AoCDay.h src/Days.h ${day_src} src/AoC.h)
