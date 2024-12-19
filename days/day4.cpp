#include "day4.h"

#ifdef TESTING
#include <catch2/catch.hpp>
#endif

namespace aoc::day4 {

Input parse_input(std::ifstream &input) {
    Input::size_type r{1}, c{0};
    std::ifstream::int_type chr;
    // Count number of columns
    for (; (chr = input.get()) != '\n'; c++)
        ;
    // Count number of rows
    while (input)
        if ((chr = input.get()) == '\n')
            r++;
    // Now that we've determined the matrix dimensions, go back to the start and read in the matrix
    input.clear(); // https://stackoverflow.com/a/28331018
    input.seekg(0);
    Input m{r, c, '.'};
    input >> m;
    return std::move(m);
}

Part1Output part1(const Input &word_search) {
    Part1Output cnt{0};

    for (auto r = 0; r < word_search.rows(); r++) {
        for (auto c = 0; c < word_search.cols(); c++) {
            if (word_search(r, c) != 'X')
                continue;

            // Forward
            if (c + 3 < word_search.cols() && word_search(r, c + 1) == 'M' && word_search(r, c + 2) == 'A' &&
                word_search(r, c + 3) == 'S')
                cnt++;

            // Down diagonal right
            if (r + 3 < word_search.rows() && c + 3 < word_search.cols() && word_search(r + 1, c + 1) == 'M' &&
                word_search(r + 2, c + 2) == 'A' && word_search(r + 3, c + 3) == 'S')
                cnt++;

            // Down
            if (r + 3 < word_search.rows() && word_search(r + 1, c) == 'M' && word_search(r + 2, c) == 'A' &&
                word_search(r + 3, c) == 'S')
                cnt++;

            // Down diagonal left
            if (r + 3 < word_search.rows() && c >= 3 && word_search(r + 1, c - 1) == 'M' &&
                word_search(r + 2, c - 2) == 'A' && word_search(r + 3, c - 3) == 'S')
                cnt++;

            // Backward
            if (c >= 3 && word_search(r, c - 1) == 'M' && word_search(r, c - 2) == 'A' && word_search(r, c - 3) == 'S')
                cnt++;

            // Up diagonal left
            if (r >= 3 && c >= 3 && word_search(r - 1, c - 1) == 'M' && word_search(r - 2, c - 2) == 'A' &&
                word_search(r - 3, c - 3) == 'S')
                cnt++;

            // Up
            if (r >= 3 && word_search(r - 1, c) == 'M' && word_search(r - 2, c) == 'A' && word_search(r - 3, c) == 'S')
                cnt++;

            // Up diagonal right
            if (r >= 3 && c + 3 < word_search.cols() && word_search(r - 1, c + 1) == 'M' &&
                word_search(r - 2, c + 2) == 'A' && word_search(r - 3, c + 3) == 'S')
                cnt++;
        }
    }

    return cnt;
}

#ifdef TESTING
TEST_CASE("day 4 sample", "[day4][sample]") {
    // clang-format off: want to keep this matrix-style formatting
    const Input input{
        {'M', 'M', 'M', 'S', 'X', 'X', 'M', 'A', 'S', 'M'}, 
        {'M', 'S', 'A', 'M', 'X', 'M', 'S', 'M', 'S', 'A'}, 
        {'A', 'M', 'X', 'S', 'X', 'M', 'A', 'A', 'M', 'M'}, 
        {'M', 'S', 'A', 'M', 'A', 'S', 'M', 'S', 'M', 'X'}, 
        {'X', 'M', 'A', 'S', 'A', 'M', 'X', 'A', 'M', 'M'}, 
        {'X', 'X', 'A', 'M', 'M', 'X', 'X', 'A', 'M', 'A'}, 
        {'S', 'M', 'S', 'M', 'S', 'A', 'S', 'X', 'S', 'S'}, 
        {'S', 'A', 'X', 'A', 'M', 'A', 'S', 'A', 'A', 'A'}, 
        {'M', 'A', 'M', 'M', 'M', 'X', 'M', 'M', 'M', 'M'}, 
        {'M', 'X', 'M', 'X', 'A', 'X', 'M', 'A', 'S', 'X'} 
    };
    // clang-format on

    SECTION("parse_input") {
        std::ifstream input_fixture{"fixtures/day4-sample-input.txt"};
        REQUIRE(input_fixture);

        const auto parsed_input{parse_input(input_fixture)};
        REQUIRE(input == parsed_input);
    }

    SECTION("part 1") {
        const auto expected = 18U, actual = part1(input);
        REQUIRE(expected == actual);
    }
}
#endif

} // namespace aoc::day4
