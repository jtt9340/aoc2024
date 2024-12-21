#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <set>

#ifdef TESTING
#include <catch2/catch.hpp>
#endif

#include "day1.h"

namespace aoc::day1 {

Input::Input(Input &&input) : left{std::move(input.left)}, right{std::move(input.right)} {}

Input parse_input(std::ifstream &input) {
    Input lists;

    enum {
        LEFT,
        RIGHT
    } which = LEFT;

    for (std::uint32_t i; input >> i;) {
        switch (which) {
        case LEFT:
            lists.left.push_back(i);
            which = RIGHT;
            break;
        case RIGHT: lists.right.push_back(i); which = LEFT;
        }
    }

    assert(lists.left.size() == lists.right.size());
    return lists;
}

Part1Output part1(Input &lists) {
    std::sort(std::begin(lists.left), std::end(lists.left));
    std::sort(std::begin(lists.right), std::end(lists.right));

    Part1Output distance{0};
    for (auto l = std::cbegin(lists.left), r = std::cbegin(lists.right);
         l != std::cend(lists.left) && r != std::cend(lists.right); l++, r++)
        distance += std::abs(static_cast<long int>(*l) - static_cast<long int>(*r));

    return distance;
}

Part2Output part2(Input &lists) {
    std::multiset<std::uint32_t> right{std::cbegin(lists.right), std::cend(lists.right)};

    Part2Output similarity_score{0};
    for (auto l : lists.left)
        similarity_score += l * right.count(l);
    return similarity_score;
}

#ifdef TESTING
TEST_CASE("day 1 sample", "[day1][sample]") {
    Input input;
    input.left = {3, 4, 2, 1, 3, 3};
    input.right = {4, 3, 5, 3, 9, 3};

    SECTION("parse_input") {
        std::ifstream input_fixture{"fixtures/day1-sample-input.txt"};
        REQUIRE(input_fixture);

        const auto parsed_input{parse_input(input_fixture)};
        REQUIRE(input.left == parsed_input.left);
        REQUIRE(input.right == parsed_input.right);
    }

    SECTION("part 1") {
        const auto expected = 11U, actual = part1(input);
        REQUIRE(expected == actual);
    }

    SECTION("part 2") {
        const auto expected = 31U, actual = part2(input);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("day 1", "[day1]") {
    std::ifstream input_fixture{"fixtures/day1-input.txt"};
    REQUIRE(input_fixture);

    auto input = parse_input(input_fixture);

    SECTION("part 1") {
        const auto expected = 2196996U, actual = part1(input);
        REQUIRE(expected == actual);
    }

    SECTION("part 2") {
        const auto expected = 23655822U, actual = part2(input);
        REQUIRE(expected == actual);
    }
}
#endif

} // namespace aoc::day1
