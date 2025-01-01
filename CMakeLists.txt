cmake_minimum_required(VERSION 3.30)
project("Advent of Code 2024" CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/days ${PROJECT_SOURCE_DIR}/util)
set(
    DAY_SOURCES
    days/day0.cpp
    days/day1.cpp
    days/day2.cpp
    days/day3.cpp
    days/day4.cpp
    days/day5.cpp
    days/day6.cpp
    days/day7.cpp
    days/day8.cpp
)
add_executable(aoc2024 aoc2024.cpp ${DAY_SOURCES})
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(aoc2024 PRIVATE -g -Werror=pessimizing-move)
endif()
install(
    TARGETS aoc2024
    DESTINATION bin
)

find_package(Catch2 REQUIRED)
add_executable(aoc2024_tests aoc2024_tests.cpp ${DAY_SOURCES} util/matrix.cpp)
target_link_libraries(aoc2024_tests PRIVATE Catch2::Catch2)
target_compile_definitions(aoc2024_tests PRIVATE TESTING)
