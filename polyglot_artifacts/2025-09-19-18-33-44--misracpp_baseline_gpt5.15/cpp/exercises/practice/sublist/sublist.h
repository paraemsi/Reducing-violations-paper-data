#pragma once

#include <algorithm>
#include <vector>
#include <initializer_list>

namespace sublist {

enum class relation { equal, sublist, superlist, unequal };
using result = relation;  // alias for compatibility
using List_comparison = relation;  // alias expected by tests

template <typename Container>
inline bool contains_subsequence(const Container& haystack, const Container& needle) {
    if (needle.begin() == needle.end()) {
        return true;
    }
    auto it = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end());
    return it != haystack.end();
}

template <typename Container>
inline bool is_sublist(const Container& sub, const Container& sup) {
    return contains_subsequence(sup, sub);
}

template <typename Container>
inline relation compare(const Container& a, const Container& b) {
    if (a == b) {
        return relation::equal;
    }
    if (is_sublist(a, b)) {
        return relation::sublist;
    }
    if (is_sublist(b, a)) {
        return relation::superlist;
    }
    return relation::unequal;
}

// Additional convenience aliases commonly used in exercises/tests
template <typename Container>
inline relation classify(const Container& a, const Container& b) {
    return compare(a, b);
}

template <typename Container>
inline relation check(const Container& a, const Container& b) {
    return compare(a, b);
}

// Public API expected by tests
template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b) {
    return compare(a, b);
}

// Overload to support calls like sublist({}, {}) where element type can't be deduced
inline List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) {
    return compare(std::vector<int>(a), std::vector<int>(b));
}

template <typename T>
inline List_comparison sublist(std::initializer_list<T> a, std::initializer_list<T> b) {
    return compare(std::vector<T>(a), std::vector<T>(b));
}

}  // namespace sublist
