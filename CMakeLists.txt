cmake_minimum_required(VERSION 3.30)
project("Advent of Code 2024" CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/days)
set(
    DAY_SOURCES
    days/day0.cpp
    days/day1.cpp
)
add_executable(aoc2024 aoc2024.cpp ${DAY_SOURCES})

#find_package(Catch2 3 REQUIRED)

#add_executable(aoc2024-test aoc2024_test.cpp)
