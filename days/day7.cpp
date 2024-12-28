#include <queue>

#include "day7.h"

#ifdef TESTING
#include <catch2/catch.hpp>
#endif

namespace aoc::day7 {

bool Equation::operator==(const Equation &eqn) const {
    return answer == eqn.answer && operands == eqn.operands;
}

bool Equation::operator!=(const Equation &eqn) const {
    return !(*this == eqn);
}

bool Equation::can_be_true() const {
    if (operands.empty())
        return false;

    std::queue<std::pair<std::size_t, std::uint64_t>> to_visit;
    to_visit.push(std::make_pair(0, operands.front()));
    while (!to_visit.empty()) {
        const auto [i, e] = to_visit.front();
        if (i < operands.size() - 1) {
            to_visit.push(std::make_pair(i + 1, e + operands[i + 1]));
            to_visit.push(std::make_pair(i + 1, e * operands[i + 1]));
        }
        if (e == answer && i == operands.size() - 1)
            return true;
        to_visit.pop();
    }

    return false;
}

Input parse_input(std::ifstream &input) {
    Input equations;

    for (std::string line; std::getline(input, line);) {
        Equation eqn;
        const auto colon = line.find(':');
        eqn.answer = std::stoull(line.substr(0, colon));

        for (auto i = colon + 2;;) {
            const auto space = line.find(' ', i);
            if (space == std::string::npos) {
                eqn.operands.push_back(std::stoull(line.substr(i)));
                break;
            } else {
                eqn.operands.push_back(std::stoull(line.substr(i, space - i)));
                i = space + 1;
            }
        }

        equations.emplace_back(std::move(eqn));
    }

    return equations;
}

Part1Output part1(const Input &input) {
    Part1Output total_calibration_result{0};

    for (const auto &eqn : input)
        if (eqn.can_be_true())
            total_calibration_result += eqn.answer;

    return total_calibration_result;
}

#ifdef TESTING
TEST_CASE("day 7 sample", "[day7][sample]") {
    Input input{{190, {10, 19}},    {3267, {81, 40, 27}},    {83, {17, 5}},
                {156, {15, 6}},     {7290, {6, 8, 6, 15}},   {161011, {16, 10, 13}},
                {192, {17, 8, 14}}, {21037, {9, 7, 18, 13}}, {292, {11, 6, 16, 20}}};

    SECTION("parse_input") {
        std::ifstream input_fixture{"fixtures/day7-sample-input.txt"};
        REQUIRE(input_fixture);

        const auto parsed_input{parse_input(input_fixture)};
        REQUIRE(input == parsed_input);
    }

    SECTION("can_be_true") {
        CHECK(input[0].can_be_true());
        CHECK(input[1].can_be_true());
        CHECK(!input[2].can_be_true());
        CHECK(!input[3].can_be_true());
        CHECK(!input[4].can_be_true());
        CHECK(!input[5].can_be_true());
        CHECK(!input[6].can_be_true());
        CHECK(!input[7].can_be_true());
        CHECK(input[8].can_be_true());
        CHECK(!Equation{2532, {8, 7, 9, 35, 4, 3, 4}}.can_be_true());
        CHECK(!Equation{172776, {3, 5, 2, 719, 3, 5, 2, 213, 1, 4}}.can_be_true());
        CHECK(!Equation{1568, {49, 16, 2, 64, 852}}.can_be_true());
    }

    SECTION("part 1") {
        const auto expected = 3749LU, actual = part1(input);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("day 7", "[day7]") {
    std::ifstream input_fixture{"fixtures/day7-input.txt"};
    REQUIRE(input_fixture);

    auto input = parse_input(input_fixture);

    SECTION("part 1") {
        const auto expected = 1399219271639LU, actual = part1(input);
        REQUIRE(expected == actual);
    }
}
#endif

} // namespace aoc::day7
