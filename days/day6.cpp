#include <algorithm>
#include <set>

#include "day6.h"

#ifdef TESTING
#include <catch2/catch.hpp>
#endif

#define loop for (;;)

namespace aoc::day6 {

Input parse_input(std::ifstream &input) {
    std::pair<Input::container_type::size_type, Input::container_type::size_type> start;
    Input::container_type::size_type rows{1}, cols{0}, c{0};
    std::ifstream::int_type chr;
    // Count number of columns
    for (; (chr = input.get()) != '\n'; cols++)
        if (chr == '^')
            start = std::make_pair(0, cols);
    // Count number of rows
    while (input) {
        switch ((chr = input.get())) {
        case '\n':
            rows++;
            c = 0;
            break;
        case '^': start = std::make_pair(rows, c);
        default: c++;
        }
    }
    // Now that we've determined the matrix dimensions, go back to the start and read in the matrix
    input.clear(); // https://stackoverflow.com/a/28331018
    input.seekg(0);
    Input::container_type m{rows, cols, '.'};
    input >> m;
    return Input{std::move(m), start};
}

Part1Output part1(const Input &input) {
    std::set<std::pair<Input::container_type::size_type, Input::container_type::size_type>> seen;
    auto cur = input.start;
    enum {
        NORTH,
        EAST,
        SOUTH,
        WEST
    } direction = NORTH;

    loop {
        seen.insert(cur);
        // Are we about to leave the maze?
        if ((direction == NORTH && cur.first == 0) || (direction == EAST && cur.second == input.maze.cols() - 1) ||
            (direction == SOUTH && cur.first == input.maze.rows() - 1) || (direction == WEST && cur.second == 0))
            break;

        switch (direction) {
        case NORTH:
            if (input.maze(cur.first - 1, cur.second) == '#')
                direction = EAST;
            else
                cur.first--;
            break;
        case EAST:
            if (input.maze(cur.first, cur.second + 1) == '#')
                direction = SOUTH;
            else
                cur.second++;
            break;
        case SOUTH:
            if (input.maze(cur.first + 1, cur.second) == '#')
                direction = WEST;
            else
                cur.first++;
            break;
        case WEST:
            if (input.maze(cur.first, cur.second - 1) == '#')
                direction = NORTH;
            else
                cur.second--;
            break;
        }
    }

    return seen.size();
}

#ifdef TESTING
TEST_CASE("day 6 sample", "[day6][sample]") {
    // clang-format off: want to keep this matrix-syle formatting
    Input input{
        {{'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
         {'.', '.', '#', '.', '.', '.', '.', '.', '.', '.'},
         {'.', '.', '.', '.', '.', '.', '.', '#', '.', '.'},
         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
         {'.', '#', '.', '.', '^', '.', '.', '.', '.', '.'},
         {'.', '.', '.', '.', '.', '.', '.', '.', '#', '.'},
         {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
         {'.', '.', '.', '.', '.', '.', '#', '.', '.', '.'}},
        std::make_pair(6, 4)
    };
    // clang-format on

    SECTION("parse_input") {
        std::ifstream input_fixture{"fixtures/day6-sample-input.txt"};
        REQUIRE(input_fixture);

        const auto parsed_input{parse_input(input_fixture)};
        CHECK(input.maze == parsed_input.maze);
        CHECK(input.start == parsed_input.start);
    }

    SECTION("part 1") {
        const Part1Output expected = 41, actual = part1(input);
        REQUIRE(expected == actual);
    }
}
#endif
} // namespace aoc::day6
