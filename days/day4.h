#include <cstdint>
#include <fstream>

#include "matrix.h"

#pragma once

namespace aoc::day4 {

using Input = dynamic_matrix<char>;
using Part1Output = std::uint32_t;
using Part2Output = std::uint32_t;

Input parse_input(std::ifstream &input);

Part1Output part1(const Input &word_search);
Part2Output part2(const Input &word_search);

} // namespace aoc::day4
