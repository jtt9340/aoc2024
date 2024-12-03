#include <array>
#include <cstdlib>
#include <sstream>
#include <string>

#ifdef TESTING
#include <catch2/catch.hpp>
#endif

#include "day2.h"

namespace aoc::day2 {

Input parse_input(std::ifstream &input) {
    Input reports;

    for (std::string report_string; std::getline(input, report_string);) {
        Input::value_type report;
        std::istringstream report_stringstream{report_string};
        for (std::array<char, 3> level_string; report_stringstream.getline(&level_string[0], 3, ' ');) {
            Input::value_type::value_type level{std::atol(level_string.data())};
            report.push_back(level);
        }

        reports.emplace_back(std::move(report));
    }

    return std::move(reports);
}

static bool is_safe(const Input::value_type &report) {
    bool increase;

    for (auto it = std::cbegin(report); it != std::cend(report) - 1; it++) {
        if (it == std::cbegin(report)) // First iteration
            increase = it[1] > *it;
        if ((it[1] > *it) != increase)
            return false;
        const auto d{std::abs(static_cast<long int>(it[1]) - static_cast<long int>(*it))};
        if (d < 1 || d > 3)
            return false;
    }

    return true;
}

Part1Output part1(const Input &reports) {
    Part1Output safe{0};

    for (const auto &report : reports)
        if (is_safe(report))
            safe++;

    return safe;
}

#ifdef TESTING
TEST_CASE("day 2 is_safe helper function", "[day2]") {
    REQUIRE(is_safe({7, 6, 4, 2, 1}));
    REQUIRE(!is_safe({1, 2, 7, 8, 9}));
    REQUIRE(!is_safe({9, 7, 6, 2, 1}));
    REQUIRE(!is_safe({1, 3, 2, 4, 5}));
    REQUIRE(!is_safe({8, 6, 4, 4, 1}));
    REQUIRE(is_safe({1, 3, 6, 7, 9}));
}

TEST_CASE("day 2 sample", "[day2][sample]") {
    // clang-format off: want to keep this matrix-style formatting
    const Input input{
        {7, 6, 4, 2, 1},
        {1, 2, 7, 8, 9},
        {9, 7, 6, 2, 1},
        {1, 3, 2, 4, 5},
        {8, 6, 4, 4, 1},
        {1, 3, 6, 7, 9}
    };
    // clang-format on

    SECTION("parse_input") {
        std::ifstream input_fixture{"fixtures/day2-sample-input.txt"};
        REQUIRE(input_fixture);

        const auto parsed_input{parse_input(input_fixture)};
        REQUIRE(input == parsed_input);
    }

    SECTION("part 1") {
        const auto expected = 2U, actual = part1(input);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("day 2", "[day2]") {
    std::ifstream input_fixture{"fixtures/day2-input.txt"};
    REQUIRE(input_fixture);

    auto input = parse_input(input_fixture);

    SECTION("part 1") {
        const auto expected = 686U, actual = part1(input);
        REQUIRE(expected == actual);
    }
}
#endif

} // namespace aoc::day2
