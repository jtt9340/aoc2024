#include <vector>

#include "day8.h"

#ifdef TESTING
#include <catch2/catch.hpp>
#endif

namespace aoc::day8 {

Input parse_input(std::ifstream &input) {
    Input i;

    std::uint8_t r = 0, c = 0;
    for (std::ifstream::char_type ch; input.get(ch);) {
        if (ch == '\n') {
            r++;
            if (!i.width)
                i.width = c;
            c = 0;
        } else {
            if (ch != '.')
                i.antennae.emplace(ch, Coord{r, c});
            c++;
        }
    }

    i.height = r;
    return i;
}

std::vector<Coord> find_antinodes(Coord a, Coord b, std::uint8_t height, std::uint8_t width) {
    std::vector<Coord> antinodes;
    antinodes.reserve(2);

    std::int16_t dx = b[1] - a[1], dy = b[0] - a[0];
    if (dx < 0)
        throw std::invalid_argument{"first coordinate must be to the left of the second one"};
    if (dy < 0) {
        if ((static_cast<std::int16_t>(a[0]) + dy) < height && (a[1] - dx) > 0)
            antinodes.emplace_back(Coord{a[0] + dy, a[1] - dx});
        if ((static_cast<std::int16_t>(b[0]) - dy) > 0 && (b[1] + dx) < width)
            antinodes.emplace_back(Coord{b[0] - dy, b[1] + dx});
    } else {
        if ((static_cast<std::int16_t>(a[0]) - dy) > 0 && (static_cast<std::int16_t>(a[1]) - dx) > 0)
            antinodes.emplace_back(Coord{a[0] - dy, a[1] - dx});
        if ((b[0] + dy) < height && (b[1] + dx) < width)
            antinodes.emplace_back(Coord{b[0] + dy, b[1] + dx});
    }

    return antinodes;
}

Part1Output part1(const Input &input) {
    return 0;
}

#ifdef TESTING
TEST_CASE("day 8 sample", "[day8][sample]") {
    Input input;
    input.height = input.width = 12;
    input.antennae = {{'0', {1, 8}}, {'0', {2, 5}}, {'0', {3, 7}}, {'0', {4, 4}},
                      {'A', {5, 6}}, {'A', {8, 8}}, {'A', {9, 9}}};

    SECTION("parse_input") {
        std::ifstream input_fixture{"fixtures/day8-sample-input.txt"};
        REQUIRE(input_fixture);

        const auto parsed_input{parse_input(input_fixture)};
        CHECK(input.height == parsed_input.height);
        CHECK(input.width == parsed_input.width);
        CHECK(input.antennae == parsed_input.antennae);
    }

    SECTION("find_antinodes") {
        CHECK(find_antinodes(Coord{2, 5}, Coord{1, 8}, 12, 12) == std::vector<Coord>{{3, 2}, {0, 11}});
        CHECK(find_antinodes(Coord{2, 5}, Coord{3, 7}, 12, 12) == std::vector<Coord>{{1, 3}, {4, 9}});
        CHECK(find_antinodes(Coord{4, 4}, Coord{2, 5}, 12, 12) == std::vector<Coord>{{6, 3}, {0, 6}});
        CHECK(find_antinodes(Coord{4, 4}, Coord{1, 8}, 12, 12) == std::vector<Coord>{{7, 0}, {0, 11}});
        CHECK(find_antinodes(Coord{4, 4}, Coord{3, 7}, 12, 12) == std::vector<Coord>{{5, 1}, {2, 10}});
        CHECK(find_antinodes(Coord{3, 7}, Coord{1, 8}, 12, 12) == std::vector<Coord>{{5, 6}});
        CHECK(find_antinodes(Coord{5, 6}, Coord{8, 8}, 12, 12) == std::vector<Coord>{{2, 4}, {11, 10}});
        CHECK(find_antinodes(Coord{5, 6}, Coord{9, 9}, 12, 12) == std::vector<Coord>{{1, 3}});
        CHECK(find_antinodes(Coord{8, 8}, Coord{9, 9}, 12, 12) == std::vector<Coord>{{7, 7}, {10, 10}});
    }
}
#endif

} // namespace aoc::day8
