#include <catch2/catch.hpp>
#include <sstream>

#include "matrix.h"

// Normally I like to include the unit tests in the same source file as the component under test but since
// the matrix classes are included in mulitple spots without doing this I get "Test case already defined."
TEST_CASE("matrix", "[util][matrix]") {
    SECTION("matrix(T) constructor fills matrix with value") {
        const matrix<std::uint32_t, 2, 2> a, b{5};
        CHECK(a(0, 0) == 0);
        CHECK(a(0, 1) == 0);
        CHECK(a(1, 0) == 0);
        CHECK(a(1, 1) == 0);
        CHECK(b(0, 0) == 5);
        CHECK(b(0, 1) == 5);
        CHECK(b(1, 0) == 5);
        CHECK(b(1, 1) == 5);
    }

    SECTION("copy constructor") {
        const matrix<std::uint32_t, 2, 2> a{5};
        const auto b{a};
        CHECK(b(0, 0) == 5);
        CHECK(b(0, 1) == 5);
        CHECK(b(1, 0) == 5);
        CHECK(b(1, 1) == 5);
    }

    SECTION("move constructor") {
        const matrix<std::uint32_t, 2, 2> a{5};
        const auto b{std::move(a)};
        CHECK(b(0, 0) == 5);
        CHECK(b(0, 1) == 5);
        CHECK(b(1, 0) == 5);
        CHECK(b(1, 1) == 5);
    }

    SECTION("initializer list") {
        // clang-format off
        const matrix<std::uint32_t, 2, 2> a {
            {1, 2},
            {3, 4}
        };
        // clang-format on
        CHECK(a(0, 0) == 1);
        CHECK(a(0, 1) == 2);
        CHECK(a(1, 0) == 3);
        CHECK(a(1, 1) == 4);
    }

    SECTION("copy assignment operator") {
        // clang-format off
        const matrix<std::uint32_t, 2, 2> a {
            {1, 2},
            {3, 4}
        };
        const matrix<std::uint32_t, 2, 3> b {
            {1, 2, 3},
            {4, 5, 6}
        };
        // clang-format on
        matrix<std::uint32_t, 2, 2> c;
        c.basic_matrix<std::uint32_t>::operator=(static_cast<const basic_matrix<std::uint32_t> &>(a));
        CHECK(c(0, 0) == 1);
        CHECK(c(0, 1) == 2);
        CHECK(c(1, 0) == 3);
        CHECK(c(1, 1) == 4);
        CHECK_THROWS_AS(c.basic_matrix<std::uint32_t>::operator=(static_cast<const basic_matrix<std::uint32_t> &>(b)),
                        std::invalid_argument);
    }

    SECTION("move assignment operator") {
        // clang-format off
        const matrix<std::uint32_t, 2, 2> a {
            {1, 2},
            {3, 4}
        };
        const matrix<std::uint32_t, 2, 3> b {
            {1, 2, 3},
            {4, 5, 6}
        };
        // clang-format on
        matrix<std::uint32_t, 2, 2> c;
        c.basic_matrix<std::uint32_t>::operator=(std::move(static_cast<const basic_matrix<std::uint32_t> &>(a)));
        CHECK(c(0, 0) == 1);
        CHECK(c(0, 1) == 2);
        CHECK(c(1, 0) == 3);
        CHECK(c(1, 1) == 4);
        CHECK_THROWS_AS(
            c.basic_matrix<std::uint32_t>::operator=(std::move(static_cast<const basic_matrix<std::uint32_t> &>(b))),
            std::invalid_argument);
    }

    // clang-format off
    matrix<std::uint32_t, 2, 2> a {
        {1, 2},
        {3, 4}
    };
    // clang-format on
    CHECK(a.rows() == 2);
    CHECK(a.cols() == 2);

    SECTION("at") {
        CHECK(a.at(0, 0) == 1);
        CHECK(a.at(0, 1) == 2);
        CHECK(a.at(1, 0) == 3);
        CHECK(a.at(1, 1) == 4);
        CHECK_THROWS_AS(a.at(2, 0), std::out_of_range);
        a.at(0, 1) = 5;
        CHECK(a.at(0, 1) == 5);
    }

    SECTION("iterators") {
        CHECK(*a.begin() == 1);
        CHECK(*a.cbegin() == 1);
        CHECK(a.begin() != a.end());
        CHECK(a.cbegin() != a.cend());
        CHECK(*a.rbegin() == 4);
        CHECK(*a.crbegin() == 4);
        CHECK(a.rbegin() != a.rend());
        CHECK(a.crbegin() != a.crend());
    }

    SECTION("swap") {
        // clang-format off
        matrix<std::uint32_t, 2, 2> a {
            {1, 2},
            {3, 4}
        };
        matrix<std::uint32_t, 2, 2> b {
            {5, 6},
            {7, 8}
        };
        matrix<std::uint32_t, 2, 3> c {
            {1, 2, 3},
            {4, 5, 6}
        };
        // clang-format on

        a.swap(b);
        CHECK(a(0, 0) == 5);
        CHECK(a(0, 1) == 6);
        CHECK(a(1, 0) == 7);
        CHECK(a(1, 1) == 8);
        CHECK(b(0, 0) == 1);
        CHECK(b(0, 1) == 2);
        CHECK(b(1, 0) == 3);
        CHECK(b(1, 1) == 4);
        CHECK_THROWS_AS(a.swap(c), std::invalid_argument);
    }

    SECTION("equality") {
        // clang-format off
        const matrix<std::uint32_t, 2, 2> expected {
            {1, 2},
            {3, 4}
        };
        const matrix<std::uint32_t, 2, 2> actual {
            {1, 2},
            {3, 4}
        };
        const matrix<std::uint32_t, 2, 2> different {
            {5, 6},
            {7, 8}
        };
        // clang-format on

        CHECK(expected == actual);
        CHECK(actual == expected);
        CHECK(expected != different);
        CHECK(different != expected);
        CHECK(actual != different);
        CHECK(different != actual);
    }

    SECTION("streams") {
        // clang-format off
        const matrix<char, 2, 2> a {
            {'a', 'b'},
            {'c', 'd'}
        };
        // clang-format on
        matrix<char, 2, 2> b;
        std::stringstream ss;
        ss << a;
        ss >> b;
        REQUIRE(a == b);
    }
}

TEST_CASE("dynamic_matrix", "[util][matrix]") {
    SECTION("dynamic_matrix(size_type, size_type, const T &) constructor fills matrix with value") {
        const dynamic_matrix<std::uint32_t> a{2, 2}, b{2, 2, 5};
        CHECK(a(0, 0) == 0);
        CHECK(a(0, 1) == 0);
        CHECK(a(1, 0) == 0);
        CHECK(a(1, 1) == 0);
        CHECK(b(0, 0) == 5);
        CHECK(b(0, 1) == 5);
        CHECK(b(1, 0) == 5);
        CHECK(b(1, 1) == 5);
    }

    SECTION("copy constructor") {
        const dynamic_matrix<std::uint32_t> a{2, 2, 5};
        const auto b{a};
        CHECK(b(0, 0) == 5);
        CHECK(b(0, 1) == 5);
        CHECK(b(1, 0) == 5);
        CHECK(b(1, 1) == 5);
    }

    SECTION("move constructor") {
        const dynamic_matrix<std::uint32_t> a{2, 2, 5};
        const auto b{std::move(a)};
        CHECK(b(0, 0) == 5);
        CHECK(b(0, 1) == 5);
        CHECK(b(1, 0) == 5);
        CHECK(b(1, 1) == 5);
    }

    SECTION("initializer list") {
        // clang-format off
        const dynamic_matrix<std::uint32_t> a {
            {1, 2},
            {3, 4}
        };
        // clang-format on
        CHECK(a(0, 0) == 1);
        CHECK(a(0, 1) == 2);
        CHECK(a(1, 0) == 3);
        CHECK(a(1, 1) == 4);
    }

    SECTION("copy assignment operator") {
        // clang-format off
        const dynamic_matrix<std::uint32_t> a {
            {1, 2},
            {3, 4}
        };
        const dynamic_matrix<std::uint32_t> b {
            {1, 2, 3},
            {4, 5, 6}
        };
        // clang-format on
        dynamic_matrix<std::uint32_t> c{2, 2};
        c.basic_matrix<std::uint32_t>::operator=(static_cast<const basic_matrix<std::uint32_t> &>(a));
        CHECK(c(0, 0) == 1);
        CHECK(c(0, 1) == 2);
        CHECK(c(1, 0) == 3);
        CHECK(c(1, 1) == 4);
        CHECK_THROWS_AS(c.basic_matrix<std::uint32_t>::operator=(static_cast<const basic_matrix<std::uint32_t> &>(b)),
                        std::invalid_argument);
    }

    SECTION("move assignment operator") {
        // clang-format off
        const dynamic_matrix<std::uint32_t> a {
            {1, 2},
            {3, 4}
        };
        const dynamic_matrix<std::uint32_t> b {
            {1, 2, 3},
            {4, 5, 6}
        };
        // clang-format on
        dynamic_matrix<std::uint32_t> c{2, 2};
        c.basic_matrix<std::uint32_t>::operator=(std::move(static_cast<const basic_matrix<std::uint32_t> &>(a)));
        CHECK(c(0, 0) == 1);
        CHECK(c(0, 1) == 2);
        CHECK(c(1, 0) == 3);
        CHECK(c(1, 1) == 4);
        CHECK_THROWS_AS(
            c.basic_matrix<std::uint32_t>::operator=(std::move(static_cast<const basic_matrix<std::uint32_t> &>(b))),
            std::invalid_argument);
    }

    // clang-format off
    dynamic_matrix<std::uint32_t> a {
        {1, 2},
        {3, 4}
    };
    // clang-format on
    CHECK(a.rows() == 2);
    CHECK(a.cols() == 2);

    SECTION("at") {
        CHECK(a.at(0, 0) == 1);
        CHECK(a.at(0, 1) == 2);
        CHECK(a.at(1, 0) == 3);
        CHECK(a.at(1, 1) == 4);
        CHECK_THROWS_AS(a.at(2, 0), std::out_of_range);
        a.at(0, 1) = 5;
        CHECK(a.at(0, 1) == 5);
    }

    SECTION("iterators") {
        CHECK(*a.begin() == 1);
        CHECK(*a.cbegin() == 1);
        CHECK(a.begin() != a.end());
        CHECK(a.cbegin() != a.cend());
        CHECK(*a.rbegin() == 4);
        CHECK(*a.crbegin() == 4);
        CHECK(a.rbegin() != a.rend());
        CHECK(a.crbegin() != a.crend());
    }

    SECTION("swap") {
        // clang-format off
        dynamic_matrix<std::uint32_t> a {
            {1, 2},
            {3, 4}
        };
        dynamic_matrix<std::uint32_t> b {
            {5, 6},
            {7, 8}
        };
        dynamic_matrix<std::uint32_t> c {
            {1, 2, 3},
            {4, 5, 6}
        };
        // clang-format on

        a.swap(b);
        CHECK(a(0, 0) == 5);
        CHECK(a(0, 1) == 6);
        CHECK(a(1, 0) == 7);
        CHECK(a(1, 1) == 8);
        CHECK(b(0, 0) == 1);
        CHECK(b(0, 1) == 2);
        CHECK(b(1, 0) == 3);
        CHECK(b(1, 1) == 4);
        CHECK_THROWS_AS(a.swap(c), std::invalid_argument);
    }

    SECTION("equality") {
        // clang-format off
        const dynamic_matrix<std::uint32_t> expected {
            {1, 2},
            {3, 4}
        };
        const dynamic_matrix<std::uint32_t> actual {
            {1, 2},
            {3, 4}
        };
        const dynamic_matrix<std::uint32_t> different {
            {5, 6},
            {7, 8}
        };
        // clang-format on

        CHECK(expected == actual);
        CHECK(actual == expected);
        CHECK(expected != different);
        CHECK(different != expected);
        CHECK(actual != different);
        CHECK(different != actual);
    }

    SECTION("streams") {
        // clang-format off
        const dynamic_matrix<char> a {
            {'a', 'b'},
            {'c', 'd'}
        };
        // clang-format on
        matrix<char, 2, 2> b;
        std::stringstream ss;
        ss << a;
        ss >> b;
        REQUIRE(a == b);
    }
}
