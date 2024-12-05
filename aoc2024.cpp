#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unistd.h>

#include "days/day0.h"
#include "days/day1.h"
#include "days/day2.h"
#include "days/day3.h"
using namespace aoc;

#define OPTSTRING "hd:p:"
#define HELP_MESSAGE                                                  \
    "[ -h ] | -d DAY [ -p PART ] INPUT_FILE\n\n"                      \
    "INPUT_FILE is a path to a file containing the puzzle input.\n\n" \
    "    -h      display this help message and exit\n"                \
    "    -d DAY  which day [0-25] to run\n"                           \
    "    -p PART which part [1-2] to run, leave unspecified for both parts"

enum class Part {
    BothParts,
    Part1,
    Part2
};

static void usage(const char *progname, int exit_code) {
    std::cout << "usage: " << progname << ' ' << HELP_MESSAGE << std::endl;
    std::exit(exit_code);
}

static int run_aoc(const long day, const Part part, std::ifstream &input) {
    auto ret = EXIT_SUCCESS;

    switch (day) {
    case 0: {
        auto input_parsed = day0::parse_input(input);
        if (part == Part::BothParts || part == Part::Part1)
            std::cout << day0::part1(input_parsed) << std::endl;
        if (part == Part::BothParts || part == Part::Part2)
            std::cout << day0::part2(input_parsed) << std::endl;
    } break;
    case 1: {
        auto input_parsed = day1::parse_input(input);
        if (part == Part::BothParts || part == Part::Part1)
            std::cout << day1::part1(input_parsed) << std::endl;
        if (part == Part::BothParts || part == Part::Part2)
            std::cout << day1::part2(input_parsed) << std::endl;
    } break;
    case 2: {
        auto input_parsed = day2::parse_input(input);
        if (part == Part::BothParts || part == Part::Part1)
            std::cout << day2::part1(input_parsed) << std::endl;
        if (part == Part::BothParts || part == Part::Part2)
            std::cout << day2::part2(input_parsed) << std::endl;
    } break;
    case 3: {
        if (part == Part::BothParts || part == Part::Part1)
            std::cout << day3::part1(input) << std::endl;
        if (part == Part::BothParts || part == Part::Part2) {
            std::cout << "error: part not yet implemented" << std::endl;
            ret = EXIT_FAILURE;
        }
    } break;
    default: std::cout << "error: day not yet implemented" << std::endl; ret = EXIT_FAILURE;
    }

    return ret;
}

int main(int argc, char *argv[]) {
    std::cout << "This is the Advent of Code 2024\n";

    const char *const progname = argv[0];
    int opt;
    char *str_end;
    auto day = -1L;
    auto part = Part::BothParts;

    while ((opt = getopt(argc, argv, OPTSTRING)) != -1) {
        switch (opt) {
        case 'd':
            day = std::strtol(optarg, &str_end, 10);
            if (optarg == str_end || day < 0 || day > 25) {
                std::cout << "error: day must be a number in the range [0-25]\n";
                usage(progname, EXIT_FAILURE);
            }
            break;
        case 'p':
            if (std::strcmp(optarg, "1") == 0)
                part = Part::Part1;
            else if (std::strcmp(optarg, "2") == 0)
                part = Part::Part2;
            else {
                std::cout << "error: part must be a number in the range [1-2]\n";
                usage(progname, EXIT_FAILURE);
            }
            break;
        case 'h': usage(progname, EXIT_SUCCESS); // fallthrough because this function never returns
        default: /* '?' */ usage(progname, EXIT_FAILURE);
        }
    }

    if (day == -1) {
        std::cout << "error: missing option -- 'd'\n";
        usage(progname, EXIT_FAILURE);
    }

    if (optind >= argc) {
        std::cout << "error: missing path to puzzle input\n";
        usage(progname, EXIT_FAILURE);
    }

    const char *const input_path = argv[optind];
    std::ifstream input{input_path};
    if (!input) {
        std::cout << "error: opening " << input_path << " failed." << std::endl;
        return EXIT_FAILURE;
    }

    return run_aoc(day, part, input);
}
