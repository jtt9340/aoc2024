#include <numeric>

#ifdef TESTING
#include <catch2/catch.hpp>
#endif

#include "day0.h"

namespace aoc::day0 {

Input parse_input(std::ifstream &input) {
    Input is;

    for (Input::value_type n; input >> n;)
        is.push_back(n);

    return is;
}

Part1Output part1(const Input &is) {
    return std::accumulate(std::cbegin(is), std::cend(is), 0, [](Input::value_type acc, Input::value_type i) {
        return acc + i;
    });
}

Part2Output part2(const Input &is) {
    return std::accumulate(std::cbegin(is), std::cend(is), 0, [](Input::value_type acc, Input::value_type i) {
        return acc * i;
    });
}

#ifdef TESTING
TEST_CASE("day 0", "[day0]") {
    const Input input{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    SECTION("parse_input") {
        std::ifstream input_fixture{"fixtures/day0-input.txt"};
        REQUIRE(input_fixture);

        const auto parsed_input{parse_input(input_fixture)};
        REQUIRE(parsed_input == input);
    }

    SECTION("part 1") {
        const auto expected = 55U, actual = part1(input);
        REQUIRE(expected == actual);
    }

    SECTION("part 2") {
        const auto expected = 0U, actual = part2(input);
        REQUIRE(expected == actual);
    }
}
#endif

} // namespace aoc::day0
