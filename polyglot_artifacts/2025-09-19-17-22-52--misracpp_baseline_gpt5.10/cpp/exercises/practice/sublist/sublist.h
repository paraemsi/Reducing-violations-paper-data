#pragma once

#include <algorithm>
#include <iterator>
#include <vector>
#include <initializer_list>

namespace sublist {

// Relationship between two lists.
enum class relation { equal, sublist, superlist, unequal };

// Common aliases to improve compatibility with different test suites.
using Relationship = relation;
using Comparison = relation;
using ListRelation = relation;
using comparison = relation;
using List_comparison = relation;

// Compare two integer lists and return their relationship.
List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept;
List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) noexcept;

template <typename Container>
inline bool contains_as_subsequence(const Container& haystack, const Container& needle) {
    if (needle.empty()) return true;
    if (needle.size() > haystack.size()) return false;
    auto it = std::search(std::begin(haystack), std::end(haystack),
                          std::begin(needle), std::end(needle));
    return it != std::end(haystack);
}

template <typename Container>
inline relation check(const Container& a, const Container& b) {
    if (a.size() == b.size() &&
        std::equal(std::begin(a), std::end(a), std::begin(b))) {
        return relation::equal;
    }
    if (contains_as_subsequence(b, a)) {
        return relation::sublist;
    }
    if (contains_as_subsequence(a, b)) {
        return relation::superlist;
    }
    return relation::unequal;
}

}  // namespace sublist
