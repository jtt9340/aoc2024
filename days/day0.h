#include <cstdint>
#include <fstream>
#include <vector>

#pragma once

namespace aoc::day0 {

using Input = std::vector<std::uint32_t>;
using Part1Output = std::uint32_t;
using Part2Output = std::uint32_t;

Input parse_input(std::ifstream &input);

Part1Output part1(const Input &is);

Part2Output part2(const Input &is);

} // namespace aoc::day0
