#include <fstream>
#include <optional>
#include <sstream>

#ifdef TESTING
#include <catch2/catch.hpp>
#endif

#include "day3.h"

namespace aoc::day3 {

static std::optional<std::uint32_t> read_and_eval_mul(std::istream &input) {
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

Part1Output part1(std::istream &input) {
    auto sum{0};

    while (!input.eof()) {
        if (auto mul = read_and_eval_mul(input))
            sum += *mul;
    }

    return sum;
}

Part2Output part2(std::istream &input) {
    auto sum{0};
    std::uint32_t a, b;
    std::istream::int_type c;
    auto enabled{true};

loop:
    while (!input.eof()) {
        switch ((c = input.get())) {
        case 'd':
            if ((c = input.get()) != 'o') {
                input.unget();
                goto loop;
            }

            switch ((c = input.get())) {
            case '(':
                if ((c = input.get()) == ')')
                    enabled = true;
                else
                    input.unget();
                goto loop;
            case 'n':
                if ((c = input.get()) != '\'') {
                    input.unget();
                    goto loop;
                }

                if ((c = input.get()) != 't') {
                    input.unget();
                    goto loop;
                }

                if ((c = input.get()) != '(') {
                    input.unget();
                    goto loop;
                }

                if ((c = input.get()) == ')')
                    enabled = false;
                else
                    input.unget();
                goto loop;
            default: input.unget(); goto loop;
            }
        case 'm':
            if ((c = input.get()) != 'u') {
                input.unget();
                goto loop;
            }

            if ((c = input.get()) != 'l') {
                input.unget();
                goto loop;
            }

            if ((c = input.get()) != '(') {
                input.unget();
                goto loop;
            }

            input >> a;
            if (input.fail())
                goto loop;

            if ((c = input.get()) != ',') {
                input.unget();
                goto loop;
            }

            input >> b;
            if (input.fail())
                goto loop;

            if ((c = input.get()) != ')') {
                input.unget();
                goto loop;
            }

            if (enabled)
                sum += a * b;
        }
    }

    return sum;
}

#ifdef TESTING
TEST_CASE("day 3 sample", "[day3][sample]") {
    SECTION("part 1") {
        std::istringstream input{"xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"};
        const auto expected = 161U, actual = part1(input);
        REQUIRE(expected == actual);
    }

    SECTION("part 2") {
        std::istringstream input{"xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"};
        const auto expected = 48U, actual = part2(input);
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

    SECTION("part 2") {
        const auto expected = 83158140U, actual = part2(input);
        REQUIRE(expected == actual);
    }
}
#endif

} // namespace aoc::day3
