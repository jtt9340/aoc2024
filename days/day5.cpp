#include <algorithm>
#include <cassert>
#include <sstream>

#include "day5.h"

#ifdef TESTING
#include <catch2/catch.hpp>

namespace Catch {
std::string StringMaker<aoc::day5::Input>::convert(const aoc::day5::Input &value) {
    std::ostringstream oss;

    for (const auto it : value.rules) {
        const auto k = it.first;
        const auto vs = it.second;
        for (const auto v : vs)
            oss << k << '|' << v << '\n';
    }

    oss << '\n';

    for (const auto &update : value.updates) {
        for (auto it = std::cbegin(update); it != std::cend(update); it++) {
            oss << *it;
            if (it != std::cend(update) - 1)
                oss << ',';
        }
        oss << '\n';
    }

    return oss.str();
}
} // namespace Catch
#endif

namespace aoc::day5 {

bool Input::operator==(const Input &other) const {
    return rules == other.rules && updates == other.updates;
}

bool Input::operator!=(const Input &other) const {
    return !(*this == other);
}

Input parse_input(std::ifstream &input) {
    Input i;

    // Parse rules
    for (std::string rule; std::getline(input, rule) && !rule.empty();) {
        std::uint32_t a, b;
        const auto n = rule.find('|');
        assert(n != std::string::npos);
        a = std::stoul(rule.substr(0, n));
        b = std::stoul(rule.substr(n + 1));
        i.rules[a].insert(b);
        i.rules.insert(std::make_pair(b, std::set<std::uint32_t>{}));
    }

    // Parse updates
    for (std::string update_s; std::getline(input, update_s);) {
        std::vector<std::uint32_t> update;
        std::istringstream iss{update_s};
        for (std::string value; std::getline(iss, value, ',');)
            update.push_back(std::stoul(value));

        i.updates.emplace_back(std::move(update));
    }

    return std::move(i);
}

static bool is_correct_order(const std::map<std::uint32_t, std::set<std::uint32_t>> &rules,
                             const std::vector<std::uint32_t> &update) {
    for (auto it = std::cbegin(update); it != std::cend(update) - 1; it++) {
        const auto e = *it, neighbor = it[1];
        if (std::find_if(std::cbegin(rules), std::cend(rules),
                         [e](const auto kv) {
                             return e == kv.first;
                         }) != std::cend(rules) &&
            std::find_if(std::cbegin(rules), std::cend(rules),
                         [neighbor](const auto kv) {
                             return neighbor == kv.first;
                         }) != std::cend(rules) &&
            std::find(std::cbegin(rules.at(e)), std::cend(rules.at(e)), neighbor) == std::cend(rules.at(e)))
            return false;
    }

    return true;
}

Part1Output part1(const Input &input) {
    Part1Output sum{0};

    for (const auto &update : input.updates) {
        if (!is_correct_order(input.rules, update))
            continue;

        sum += update[update.size() / 2];
    }

    return sum;
}

#ifdef TESTING
TEST_CASE("day 5 sample", "[day5][sample]") {
    Input input;
    input.rules = {{47, {53, 13, 61, 29}},
                   {97, {13, 61, 47, 29, 53, 75}},
                   {75, {29, 53, 47, 61, 13}},
                   {61, {13, 53, 29}},
                   {29, {13}},
                   {53, {29, 13}},
                   {13, {}}};
    input.updates = {{75, 47, 61, 53, 29}, {97, 61, 53, 29, 13}, {75, 29, 13},
                     {75, 97, 47, 61, 53}, {61, 13, 29},         {97, 13, 75, 29, 47}};

    SECTION("parse_input") {
        std::ifstream input_fixture{"fixtures/day5-sample-input.txt"};
        REQUIRE(input_fixture);

        const auto parsed_input{parse_input(input_fixture)};
        REQUIRE(input == parsed_input);
    }

    SECTION("is_correct_order") {
        CHECK(is_correct_order(input.rules, input.updates[0]));
        CHECK(is_correct_order(input.rules, input.updates[1]));
        CHECK(is_correct_order(input.rules, input.updates[2]));
        CHECK(!is_correct_order(input.rules, input.updates[3]));
        CHECK(!is_correct_order(input.rules, input.updates[4]));
        CHECK(!is_correct_order(input.rules, input.updates[5]));
        CHECK(is_correct_order(input.rules, {75, 100, 29, 13}));
    }

    SECTION("part 1") {
        const auto expected = 143U, actual = part1(input);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("day 5", "[day5]") {
    std::ifstream input_fixture{"fixtures/day5-input.txt"};
    REQUIRE(input_fixture);

    auto input = parse_input(input_fixture);

    SECTION("part 1") {
        const auto expected = 6612U, actual = part1(input);
        REQUIRE(expected == actual);
    }
}
#endif

} // namespace aoc::day5
