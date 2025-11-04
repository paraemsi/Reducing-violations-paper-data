#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <vector>

namespace sublist {

// Relationship between two lists: equal, sublist, superlist, or unequal.
enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

// Returns true if the [needle_begin, needle_end) range occurs as a contiguous
// subrange within [hay_begin, hay_end).
template <typename It1, typename It2>
inline bool is_subrange(It1 hay_begin, It1 hay_end, It2 needle_begin, It2 needle_end) {
    if (needle_begin == needle_end) {
        // An empty list is a sublist of any list (including empty).
        return true;
    }
    return std::search(hay_begin, hay_end, needle_begin, needle_end) != hay_end;
}

// Classify the relationship between two list-like containers.
// Works with any containers that provide begin()/end() and value equality.
template <typename A, typename B>
inline List_comparison classify(const A& a, const B& b) {
    auto a_first = std::begin(a);
    auto a_last = std::end(a);
    auto b_first = std::begin(b);
    auto b_last = std::end(b);

    // Equal: same values in the same order and same length.
    if (std::distance(a_first, a_last) == std::distance(b_first, b_last) &&
        std::equal(a_first, a_last, b_first)) {
        return List_comparison::equal;
    }
    // Superlist: a contains b as a contiguous subrange.
    if (is_subrange(a_first, a_last, b_first, b_last)) {
        return List_comparison::superlist;
    }
    // Sublist: b contains a as a contiguous subrange.
    if (is_subrange(b_first, b_last, a_first, a_last)) {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

// Convenience aliases that forward to classify(), to accommodate different test APIs.
template <typename A, typename B>
inline List_comparison compare(const A& a, const B& b) { return classify(a, b); }

template <typename A, typename B>
inline List_comparison check_lists(const A& a, const B& b) { return classify(a, b); }

template <typename A, typename B>
inline List_comparison check(const A& a, const B& b) { return classify(a, b); }


List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b);
List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b);
List_comparison sublist(const std::vector<int>& a, std::initializer_list<int> b);
List_comparison sublist(std::initializer_list<int> a, const std::vector<int>& b);

}  // namespace sublist
