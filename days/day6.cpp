#include <algorithm>
#include <set>

#include "day6.h"

#ifdef TESTING
#include <catch2/catch.hpp>
#endif

#define loop for (;;)

namespace aoc::day6 {

enum class Direction {
    North,
    East,
    South,
    West
};

using seen_set = std::set<std::tuple<Input::container_type::size_type, Input::container_type::size_type, Direction>>;

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
    auto direction = Direction::North;

    loop {
        seen.insert(cur);
        // Are we about to leave the maze?
        if ((direction == Direction::North && cur.first == 0) ||
            (direction == Direction::East && cur.second == input.maze.cols() - 1) ||
            (direction == Direction::South && cur.first == input.maze.rows() - 1) ||
            (direction == Direction::West && cur.second == 0))
            break;

        switch (direction) {
        case Direction::North:
            if (input.maze(cur.first - 1, cur.second) == '#')
                direction = Direction::East;
            else
                cur.first--;
            break;
        case Direction::East:
            if (input.maze(cur.first, cur.second + 1) == '#')
                direction = Direction::South;
            else
                cur.second++;
            break;
        case Direction::South:
            if (input.maze(cur.first + 1, cur.second) == '#')
                direction = Direction::West;
            else
                cur.first++;
            break;
        case Direction::West:
            if (input.maze(cur.first, cur.second - 1) == '#')
                direction = Direction::North;
            else
                cur.second--;
            break;
        }
    }

    return seen.size();
}

static bool simulate(const seen_set &seen, const Input::container_type &maze,
                     std::pair<Input::container_type::size_type, Input::container_type::size_type> cur,
                     Direction direction) {
    seen_set simulated_seen{seen};
    loop {
        if (!simulated_seen.insert(std::make_tuple(cur.first, cur.second, direction)).second)
            return true;
        // Are we about to leave the maze?
        if ((direction == Direction::North && cur.first == 0) ||
            (direction == Direction::East && cur.second == maze.cols() - 1) ||
            (direction == Direction::South && cur.first == maze.rows() - 1) ||
            (direction == Direction::West && cur.second == 0))
            break;

        switch (direction) {
        case Direction::North:
            if (maze(cur.first - 1, cur.second) == '#')
                direction = Direction::East;
            else
                cur.first--;
            break;
        case Direction::East:
            if (maze(cur.first, cur.second + 1) == '#')
                direction = Direction::South;
            else
                cur.second++;
            break;
        case Direction::South:
            if (maze(cur.first + 1, cur.second) == '#')
                direction = Direction::West;
            else
                cur.first++;
            break;
        case Direction::West:
            if (maze(cur.first, cur.second - 1) == '#')
                direction = Direction::North;
            else
                cur.second--;
            break;
        }
    }

    return false;
}

Part2Output part2(const Input &input) {
    seen_set seen;
    auto cur = input.start;
    auto direction = Direction::North;
    Part2Output cnt{0};

    loop {
        seen.insert(std::make_tuple(cur.first, cur.second, direction));
        // Are we about to leave the maze?
        if ((direction == Direction::North && cur.first == 0) ||
            (direction == Direction::East && cur.second == input.maze.cols() - 1) ||
            (direction == Direction::South && cur.first == input.maze.rows() - 1) ||
            (direction == Direction::West && cur.second == 0))
            break;

        switch (direction) {
        case Direction::North:
            if (input.maze(cur.first - 1, cur.second) == '#') {
                direction = Direction::East;
            } else {
                for (auto c = cur.second; c < input.maze.cols(); c++) {
                    if (input.maze(cur.first, c) == '#') {
                        if (simulate(seen, input.maze, cur, Direction::East))
                            cnt++;
                        break;
                    }
                }
                cur.first--;
            }
            break;
        case Direction::East:
            if (input.maze(cur.first, cur.second + 1) == '#') {
                direction = Direction::South;
            } else {
                for (auto r = cur.first; r < input.maze.rows(); r++) {
                    if (input.maze(r, cur.second) == '#') {
                        if (simulate(seen, input.maze, cur, Direction::South))
                            cnt++;
                        break;
                    }
                }
                cur.second++;
            }
            break;
        case Direction::South:
            if (input.maze(cur.first + 1, cur.second) == '#') {
                direction = Direction::West;
            } else {
                for (auto c = cur.second; c <= cur.second; c--) {
                    if (input.maze(cur.first, c) == '#') {
                        if (simulate(seen, input.maze, cur, Direction::West))
                            cnt++;
                        break;
                    }
                }
                cur.first++;
            }
            break;
        case Direction::West:
            if (input.maze(cur.first, cur.second - 1) == '#') {
                direction = Direction::North;
            } else {
                for (auto r = cur.first; r <= cur.first; r--) {
                    if (input.maze(r, cur.second) == '#') {
                        if (simulate(seen, input.maze, cur, Direction::North))
                            cnt++;
                        break;
                    }
                }
                cur.second--;
            }
            break;
        }
    }

    return cnt;
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

    SECTION("part 2") {
        const Part2Output expected = 6U, actual = part2(input);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("day 6", "[day6]") {
    std::ifstream input_fixture{"fixtures/day6-input.txt"};
    REQUIRE(input_fixture);

    auto input = parse_input(input_fixture);

    SECTION("part 1") {
        const Part1Output expected = 4647U, actual = part1(input);
        REQUIRE(expected == actual);
    }

    SECTION("part 2") {
        // TODO GET THIS TO PASS
        REQUIRE(part2(input) < 1826);
    }
}
#endif
} // namespace aoc::day6
