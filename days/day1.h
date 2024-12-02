#include <cstdint>
#include <fstream>
#include <vector>

#pragma once

namespace aoc::day1 {

struct Input {
    std::vector<std::uint32_t> left, right;

    Input() = default;
    Input(Input &&input);
};

using Part1Output = std::uint32_t;

Input parse_input(std::ifstream &input);

Part1Output part1(Input &lists);

} // namespace aoc::day1
