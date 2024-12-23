#include <fstream>
#include <utility>

#include "matrix.h"

#pragma once

namespace aoc::day6 {

struct Input {
    using container_type = dynamic_matrix<char>;
    container_type maze;
    std::pair<container_type::size_type, container_type::size_type> start;
};

using Part1Output = std::size_t;

Input parse_input(std::ifstream &input);

Part1Output part1(const Input &input);

} // namespace aoc::day6
