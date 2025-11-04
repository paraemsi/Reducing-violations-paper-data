#pragma once

#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <vector>

namespace sublist {

enum class Comparison { equal, sublist, superlist, unequal };
using List_comparison = Comparison;

// trait to detect std::initializer_list
template <typename>
struct is_initializer_list : std::false_type {};

template <typename T>
struct is_initializer_list<std::initializer_list<T>> : std::true_type {};

template <typename Container>
inline bool is_subvector(const Container& small, const Container& large) {
    if (small.empty()) {
        return true;
    }
    if (small.size() > large.size()) {
        return false;
    }
    auto it = std::search(large.begin(), large.end(), small.begin(), small.end());
    return it != large.end();
}

template <typename Container>
inline Comparison check(const Container& a, const Container& b) {
    if (a == b) {
        return Comparison::equal;
    }
    if (is_subvector(a, b)) {
        return Comparison::sublist;
    }
    if (is_subvector(b, a)) {
        return Comparison::superlist;
    }
    return Comparison::unequal;
}

template <typename Container, std::enable_if_t<!is_initializer_list<Container>::value, int> = 0>
inline List_comparison sublist(const Container& a, const Container& b) {
    return check(a, b);
}

template <typename T>
inline List_comparison sublist(std::initializer_list<T> a, std::initializer_list<T> b) {
    return check(std::vector<T>(a), std::vector<T>(b));
}

// Handle the case where both initializer_lists are empty (type cannot be deduced)
inline List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) {
    return check(std::vector<int>(a), std::vector<int>(b));
}

}  // namespace sublist
