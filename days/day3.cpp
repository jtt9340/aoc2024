#include <optional>

#ifdef TESTING
#include <catch2/catch.hpp>
#endif

#include "day3.h"

namespace aoc::day3 {

static std::optional<std::uint32_t> read_and_eval_mul(std::ifstream &input) {
    std::uint32_t a, b;
    std::ifstream::int_type c;

    if ((c = input.get()) != 'm')
        return std::nullopt;

    if ((c = input.get()) != 'u')
        return std::nullopt;

    if ((c = input.get()) != 'l')
        return std::nullopt;

    if ((c = input.get()) != '(')
        return std::nullopt;

    input >> a;
    if (input.fail())
        return std::nullopt;

    if ((c = input.get()) != ',')
        return std::nullopt;

    input >> b;
    if (input.fail())
        return std::nullopt;

    if ((c = input.get()) != ')')
        return std::nullopt;

    return a * b;
}

Part1Output part1(std::ifstream &input) {
    auto sum{0};

    while (!input.eof()) {
        if (auto mul = read_and_eval_mul(input))
            sum += *mul;
    }

    return sum;
}

#ifdef TESTING
TEST_CASE("day 3 sample", "[day3][sample]") {
    std::ifstream input{"fixtures/day3-sample-input.txt"};
    REQUIRE(input);

    SECTION("part 1") {
        const auto expected = 161U, actual = part1(input);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("day 3", "[day3]") {
    std::ifstream input{"fixtures/day3-input.txt"};
    REQUIRE(input);

    SECTION("part 1") {
        const auto expected = 173785482U, actual = part1(input);
        REQUIRE(expected == actual);
    }
}
#endif

} // namespace aoc::day3
