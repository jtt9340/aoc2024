#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <set>

#include "day1.h"

namespace aoc::day1 {

Input::Input(Input &&input) : left{std::move(input.left)}, right{std::move(input.right)} {}

Input parse_input(std::ifstream &input) {
    Input lists;

    enum {
        LEFT,
        RIGHT
    } which = LEFT;

    for (std::uint32_t i; input >> i;) {
        switch (which) {
        case LEFT:
            lists.left.push_back(i);
            which = RIGHT;
            break;
        case RIGHT: lists.right.push_back(i); which = LEFT;
        }
    }

    assert(lists.left.size() == lists.right.size());
    return std::move(lists);
}

Part1Output part1(Input &lists) {
    std::sort(std::begin(lists.left), std::end(lists.left));
    std::sort(std::begin(lists.right), std::end(lists.right));

    Part1Output distance{0};
    for (auto l = std::cbegin(lists.left), r = std::cbegin(lists.right);
         l != std::cend(lists.left) && r != std::cend(lists.right); l++, r++)
        distance += std::abs(static_cast<long int>(*l) - static_cast<long int>(*r));

    return distance;
}

Part2Output part2(Input &lists) {
    std::multiset<std::uint32_t> right{std::cbegin(lists.right), std::cend(lists.right)};

    Part2Output similarity_score{0};
    for (auto l : lists.left)
        similarity_score += l * right.count(l);
    return similarity_score;
}

} // namespace aoc::day1
