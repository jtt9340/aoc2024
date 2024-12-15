#include <algorithm>
#include <array>
#include <cstdlib>
#include <initializer_list>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <vector>

#ifdef TESTING
#include <catch2/catch.hpp>
#include <sstream>
#endif

#pragma once

template <class T>
class basic_matrix {
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;

    basic_matrix<T> &operator=(const basic_matrix<T> &other) {
        if (rows() != other.rows() || cols() != other.cols())
            throw std::invalid_argument{"matrix on rhs has invalid dimensions"};
        for (auto i = 0; i < other.rows(); i++)
            for (auto j = 0; j < other.cols(); j++)
                (*this)(i, j) = other(i, j);
        return *this;
    }

    basic_matrix<T> &operator=(basic_matrix<T> &&other) {
        if (rows() != other.rows() || cols() != other.cols())
            throw std::invalid_argument{"matrix on rhs has invalid dimensions"};
        for (auto i = 0; i < other.rows(); i++)
            for (auto j = 0; j < other.cols(); j++)
                (*this)(i, j) = std::move(other(i, j));
        return *this;
    }

    basic_matrix<T> &operator=(std::initializer_list<std::initializer_list<value_type>> ilist) {
        if (ilist.size() != rows())
            throw std::invalid_argument{"initializer list has wrong number of rows"};
        size_type i = 0, j = 0;
        for (auto row : ilist) {
            if (row.size() != cols())
                throw std::invalid_argument{"initializer list has wrong number of columns"};
            for (auto x : row)
                (*this)(i, j++) = x;
            i++;
            j = 0;
        }
        return *this;
    }

    virtual reference at(size_type row, size_type col) = 0;
    virtual const_reference at(size_type row, size_type col) const = 0;
    virtual reference operator()(size_type row, size_type col) = 0;
    virtual const_reference operator()(size_type row, size_type col) const = 0;

    virtual pointer data() = 0;
    virtual const_pointer data() const = 0;

    virtual size_type rows() const = 0;
    virtual size_type cols() const = 0;

    void swap(basic_matrix<T> &other) {
        if (rows() != other.rows() || cols() != other.cols())
            throw std::invalid_argument{"matrix to swap with has invalid dimensions"};
        for (auto i = 0; i < other.rows(); i++)
            for (auto j = 0; j < other.cols(); j++)
                std::swap((*this)(i, j), other(i, j));
    }
};

template <class T>
std::ostream &operator<<(std::ostream &out, const basic_matrix<T> &m) {
    for (auto i = 0; i < m.rows(); i++) {
        for (auto j = 0; j < m.cols(); j++)
            out << m(i, j);
        out << '\n';
    }

    return out;
}

template <class T>
std::istream &operator>>(std::istream &in, basic_matrix<T> &m) {
    for (auto i = 0; i < m.rows(); i++) {
        for (auto j = 0; j < m.cols(); j++) {
            T x;
            in >> x;
            if (in.bad() || in.eof())
                return in;
            if (in.fail())
                continue;
            m(i, j) = x;
        }
    }

    return in;
}

template <class T>
bool operator==(const basic_matrix<T> &lhs, const basic_matrix<T> &rhs) {
    if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
        return false;

    for (auto i = 0; i < lhs.rows(); i++)
        for (auto j = 0; j < rhs.rows(); j++)
            if (lhs(i, j) != rhs(i, j))
                return false;

    return true;
}

template <class T>
bool operator!=(const basic_matrix<T> &lhs, const basic_matrix<T> &rhs) {
    return !(lhs == rhs);
}

template <class T, std::size_t R, std::size_t C>
class matrix : public basic_matrix<T> {
    std::array<T, R * C> arr;
    using arr_type = decltype(arr);

public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = typename arr_type::iterator;
    using const_iterator = typename arr_type::const_iterator;
    using reverse_iterator = typename arr_type::reverse_iterator;
    using const_reverse_iterator = typename arr_type::const_reverse_iterator;

    matrix(const T &x = T()) {
        std::fill(std::begin(arr), std::end(arr), x);
    }

    matrix(const matrix<T, R, C> &other) {
        std::copy(std::cbegin(other.arr), std::cend(other.arr), std::begin(arr));
    }

    matrix(matrix<T, R, C> &&other) {
        std::move(std::begin(other.arr), std::end(other.arr), std::begin(arr));
    }

    matrix(std::initializer_list<std::initializer_list<value_type>> ilist) {
        basic_matrix<T>::operator=(ilist);
    }

    reference at(size_type row, size_type col) {
        return arr.at(C * row + col);
    }

    const_reference at(size_type row, size_type col) const {
        return arr.at(C * row + col);
    }

    reference operator()(size_type row, size_type col) {
        return arr[C * row + col];
    }

    const_reference operator()(size_type row, size_type col) const {
        return arr[C * row + col];
    }

    pointer data() {
        return arr.data();
    }

    const_pointer data() const {
        return arr.data();
    }

    iterator begin() {
        return std::begin(arr);
    }

    const_iterator begin() const {
        return std::cbegin(arr);
    }

    const_iterator cbegin() const {
        return std::cbegin(arr);
    }

    iterator end() {
        return std::end(arr);
    }

    const_iterator end() const {
        return std::cend(arr);
    }

    const_iterator cend() const {
        return std::cend(arr);
    }

    reverse_iterator rbegin() {
        return std::rbegin(arr);
    }

    const_reverse_iterator rbegin() const {
        return std::crbegin(arr);
    }

    const_reverse_iterator crbegin() const {
        return std::crbegin(arr);
    }

    reverse_iterator rend() {
        return std::rend(arr);
    }

    const_reverse_iterator rend() const {
        return std::crend(arr);
    }

    const_reverse_iterator crend() const {
        return std::crend(arr);
    }

    inline size_type rows() const {
        return R;
    }

    inline size_type cols() const {
        return C;
    }
};

template <class T>
class dynamic_matrix : public basic_matrix<T> {
    std::vector<T> vec;
    using vec_type = decltype(vec);
    typename vec_type::size_type r, c;

public:
    using value_type = T;
    using size_type = typename vec_type::size_type;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = typename vec_type::iterator;
    using const_iterator = typename vec_type::const_iterator;
    using reverse_iterator = typename vec_type::reverse_iterator;
    using const_reverse_iterator = typename vec_type::const_reverse_iterator;

    dynamic_matrix(size_type r, size_type c, const T &x = T()) : r{r}, c{c}, vec(r * c, x) {}
    dynamic_matrix(const dynamic_matrix<T> &other) : r{other.r}, c{other.c}, vec{other.vec} {}
    dynamic_matrix(dynamic_matrix<T> &&other) : r{other.r}, c{other.c}, vec{std::move(other.vec)} {}
    dynamic_matrix(std::initializer_list<std::initializer_list<value_type>> ilist) : r{ilist.size()} {
        auto it{std::begin(ilist)};
        c = it->size();
        for (; it != std::end(ilist); it++) {
            if (it->size() != c)
                throw std::invalid_argument{"initializer list has wrong number of columns"};
            vec.insert(std::cend(vec), *it);
        }
    }

    reference at(size_type row, size_type col) {
        return vec.at(row * cols() + col);
    }

    const_reference at(size_type row, size_type col) const {
        return vec.at(row * cols() + col);
    }

    reference operator()(size_type row, size_type col) {
        return vec[row * cols() + col];
    }

    const_reference operator()(size_type row, size_type col) const {
        return vec[row * cols() + col];
    }

    pointer data() {
        return vec.data();
    }

    const_pointer data() const {
        return vec.data();
    }

    iterator begin() {
        return std::begin(vec);
    }

    const_iterator begin() const {
        return std::cbegin(vec);
    }

    const_iterator cbegin() const {
        return std::cbegin(vec);
    }

    iterator end() {
        return std::end(vec);
    }

    const_iterator end() const {
        return std::cend(vec);
    }

    const_iterator cend() const {
        return std::cend(vec);
    }

    reverse_iterator rbegin() {
        return std::rbegin(vec);
    }

    const_reverse_iterator rbegin() const {
        return std::crbegin(vec);
    }

    const_reverse_iterator crbegin() const {
        return std::crbegin(vec);
    }

    reverse_iterator rend() {
        return std::rend(vec);
    }

    const_reverse_iterator rend() const {
        return std::crend(vec);
    }

    const_reverse_iterator crend() const {
        return std::crend(vec);
    }

    size_type rows() const {
        return r;
    }

    size_type cols() const {
        return c;
    }
};

#ifdef TESTING
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
#endif
