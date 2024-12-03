#include <cstdint>
#include <fstream>
#include <vector>

#pragma once

namespace aoc::day2 {

using Input = std::vector<std::vector<std::uint32_t>>;
using Part1Output = std::uint32_t;

Input parse_input(std::ifstream &input);

Part1Output part1(const Input &reports);

} // namespace aoc::day2
