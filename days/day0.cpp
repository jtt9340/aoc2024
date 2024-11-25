#include <numeric>

#include "day0.h"

namespace aoc::day0 {

Input parse_input(std::ifstream &input) {
    Input is;

    for (Input::value_type n; input >> n;)
        is.push_back(n);

    return std::move(is);
}

Part1Output part1(Input &is) {
    return std::accumulate(std::cbegin(is), std::cend(is), 0, [](Input::value_type acc, Input::value_type i) {
        return acc + i;
    });
}

Part2Output part2(Input &is) {
    return std::accumulate(std::cbegin(is), std::cend(is), 0, [](Input::value_type acc, Input::value_type i) {
        return acc * i;
    });
}

} // namespace aoc::day0
