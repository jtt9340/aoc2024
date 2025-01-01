#include <array>
#include <cstdint>
#include <fstream>
#include <map>

#pragma once

namespace aoc::day8 {
using Coord = std::array<std::uint8_t, 2>;

struct Input {
    std::uint8_t height = 0, width = 0;
    std::multimap<char, Coord> antennae;
};

using Part1Output = std::uint32_t;

Input parse_input(std::ifstream &input);

Part1Output part1(const Input &input);

} // namespace aoc::day8
