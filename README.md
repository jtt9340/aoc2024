# [Advent of Code 2024][aoc]
My solutions to the Advent of Code 2024, or, at least as many days as I can do.

* Each solution is in its own day file in the [`days/`](./days) directory.
* Puzzle inputs, including sample ones given in puzzle descriptions and the actual puzzle inputs, live in the [`fixtures/`](./fixtures) directory.
* There is a binary that will run a given day -- the code for that lives in [`aoc2024.cpp`](./aoc2024.cpp).
* I am using the [Catch2 library][catch2] to unit test each day's solution. A separate binary, whose code is contained in [`aoc2024_tests.cpp`](./aoc2024_tests.cpp), runs the unit tests.

## Building and Running using [Nix][nix]
You can run the main binary just by doing `nix run . --`, e.g. `nix run . -- -d 1 fixtures/day1-input.txt`.

If you want to compile the binaries manually with CMake (see below), you can enter a developer shell with `nix develop`.
This is currently the only way to build and run the test binary.

## Building and Running outside of Nix
This is a [CMake][cmake] project. You will need the aforementioned Catch2 library installed.
```sh
mkdir build && cd build
cmake ..
cmake --build .
./aoc2024 -h
./aoc2024_tests -h
# Optionally
cmake --install . --prefix $(dirname $PWD)
```

[aoc]: https://adventofcode.com/2024
[nix]: https://nixos.org/
[catch2]: https://github.com/catchorg/Catch2/tree/v2.x/
[cmake]: https://cmake.org/
