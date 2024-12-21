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

    return reports;
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

#if 0
// TODO GET THIS TO WORK IN O(n) TIME
static bool is_safe_with_problem_dampener(const Input::value_type &report) {
    bool increase;
    bool removed{false};

    for (auto it = std::cbegin(report); it != std::cend(report) - 1; it++) {
        if (it == std::cbegin(report)) // First iteration
            increase = it[1] > *it;
        if ((it[1] > *it) != increase && !removed) {
           // Consider removing *it
           if (it == std::cend(report) - 2)
              return true; // If the offending level is the last one then deleting it will make the level valid
           const auto d{std::abs(static_cast<long int>(it[1]) - static_cast<long int>(it[-1]))};
           if (d < 1 || d > 3 || (it[1] > it[-1]) != increase)
               return false;
           removed = true;
           continue;
        } else if ((it[1] > *it) != increase)
            return false;
        auto d{std::abs(static_cast<long int>(it[1]) - static_cast<long int>(*it))};
        if ((d < 1 || d > 3) && !removed) {
            // Consider removing it
            if (it == std::cbegin(report)) {
                // If the offending level is the first one we can just remove it without checking the validity of the resulting report
                removed = true;
                increase = it[2] > it[1];
                continue;
            }

            if (it == std::cend(report) - 2)
                return true; // If the offending level is the last one then deleting it will make the level valid

            d = std::abs(static_cast<long int>(it[1]) - static_cast<long int>(it[-1]));
            if (d < 1 || d > 3 || (it[1] > it[-1]) != increase) {
                if (it + 1 != std::cend(report) - 1) {
                    // Consider removing one after it
                    d = std::abs(static_cast<long int>(it[2]) - static_cast<long int>(*it));
                    if (d < 1 || d > 3 || (it[2] > *it) != increase)
                        return false;
                    it++;
                } else
                    return false;
            }
            removed = true;
        } else if (d < 1 || d > 3)
            return false;
    }

    return true;
}
#endif

static bool is_safe_with_problem_dampener(const Input::value_type &reports) {
    if (is_safe(reports))
        return true;

    Input::value_type rs{reports};
    for (auto it = std::begin(rs); it != std::end(rs); it++) {
        const auto e{*it};
        rs.erase(it);
        if (is_safe(rs))
            return true;
        rs.insert(it, e);
    }

    return false;
}

template <bool (*safety_func)(const Input::value_type &)>
static std::uint32_t determine_safety(const Input &reports) {
    std::uint32_t safe{0};

    for (const auto &report : reports)
        if (safety_func(report))
            safe++;

    return safe;
}

Part1Output part1(const Input &reports) {
    return determine_safety<is_safe>(reports);
}

Part2Output part2(const Input &reports) {
    return determine_safety<is_safe_with_problem_dampener>(reports);
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

TEST_CASE("day 2 is_safe_with_problem_dampener helper function", "[day2]") {
    REQUIRE(is_safe_with_problem_dampener({7, 6, 4, 2, 1}));
    REQUIRE(!is_safe_with_problem_dampener({1, 2, 7, 8, 9}));
    REQUIRE(!is_safe_with_problem_dampener({9, 7, 6, 2, 1}));
    REQUIRE(is_safe_with_problem_dampener({1, 3, 2, 4, 5}));
    REQUIRE(is_safe_with_problem_dampener({8, 6, 4, 4, 1}));
    REQUIRE(is_safe_with_problem_dampener({1, 3, 6, 7, 9}));
    REQUIRE(is_safe_with_problem_dampener({1, 1, 2, 3, 4}));
    REQUIRE(is_safe_with_problem_dampener({1, 2, 3, 4, 4}));
    REQUIRE(is_safe_with_problem_dampener({1, 3, 5, 6, 8, 9, 13, 10}));
    REQUIRE(is_safe_with_problem_dampener({4, 1, 2, 5, 7, 9}));
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

    SECTION("part 2") {
        const auto expected = 4U, actual = part2(input);
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

    SECTION("part 2") {
        const auto expected = 717U, actual = part2(input);
        REQUIRE(expected == actual);
    }
}
#endif

} // namespace aoc::day2
