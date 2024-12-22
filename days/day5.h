#include <cstdint>
#include <fstream>
#include <map>
#include <set>
#include <vector>

#pragma once

namespace aoc::day5 {
struct Input {
    std::map<std::uint32_t, std::set<std::uint32_t>> rules;
    std::vector<std::vector<std::uint32_t>> updates;

    Input() = default;
    Input(Input &&input) = default;

    bool operator==(const Input &other) const;
    bool operator!=(const Input &other) const;
};

using Part1Output = std::uint32_t;
using Part2Output = std::uint32_t;

Input parse_input(std::ifstream &input);

Part1Output part1(const Input &input);
Part2Output part2(const Input &input);
} // namespace aoc::day5

#ifdef TESTING
#include <catch2/catch.hpp>

namespace Catch {
template <>
struct StringMaker<aoc::day5::Input> {
    static std::string convert(const aoc::day5::Input &value);
};
} // namespace Catch
#endif
