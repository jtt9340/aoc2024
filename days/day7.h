#include <cstdint>
#include <fstream>
#include <vector>

#pragma once

namespace aoc::day7 {

struct Equation {
    std::uint64_t answer;
    std::vector<std::uint64_t> operands;

    bool operator==(const Equation &eqn) const;
    bool operator!=(const Equation &eqn) const;

    bool can_be_true() const;
};

using Input = std::vector<Equation>;
using Part1Output = std::uint64_t;

Input parse_input(std::ifstream &input);

Part1Output part1(const Input &input);

} // namespace aoc::day7
