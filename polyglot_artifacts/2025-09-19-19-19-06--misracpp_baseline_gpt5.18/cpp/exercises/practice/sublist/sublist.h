#pragma once

#include <iterator>
#include <algorithm>
#include <initializer_list>

namespace sublist {

// Relationship between two lists.
enum class comparison { equal, sublist, superlist, unequal };

// Helper: does [needle_begin, needle_end) occur contiguously inside [hay_begin, hay_end)?
template <typename It1, typename It2>
inline bool contains_subsequence(It1 hay_begin, It1 hay_end, It2 needle_begin, It2 needle_end) {
    if (needle_begin == needle_end) {
        // An empty sequence is a sub-sequence of any sequence (including empty)
        return true;
    }
    return std::search(hay_begin, hay_end, needle_begin, needle_end) != hay_end;
}

// Classify relationship between two ranges (containers, arrays, initializer_lists, etc.)
template <typename RangeA, typename RangeB>
inline comparison classify(const RangeA& a, const RangeB& b) {
    auto begin1 = std::begin(a);
    auto begin2 = std::begin(b);
    auto end1 = std::end(a);
    auto end2 = std::end(b);
    auto it1 = begin1;
    auto it2 = begin2;

    // Equality check without precomputing sizes
    for (; it1 != end1 && it2 != end2; ++it1, ++it2) {
        if (!(*it1 == *it2)) {
            break;
        }
    }
    if (it1 == end1 && it2 == end2) {
        return comparison::equal;
    }

    if (contains_subsequence(begin1, end1, begin2, end2)) {
        return comparison::superlist;
    }
    if (contains_subsequence(begin2, end2, begin1, end1)) {
        return comparison::sublist;
    }
    return comparison::unequal;
}

 // Convenience aliases for potential test naming variations.
using result = comparison;
using relationship = comparison;
using classification = comparison;
using List_comparison = comparison;

template <typename RangeA, typename RangeB>
inline List_comparison compare(const RangeA& a, const RangeB& b) {
    return classify(a, b);
}

template <typename RangeA, typename RangeB>
inline List_comparison check(const RangeA& a, const RangeB& b) {
    return classify(a, b);
}

// Provide the function named `sublist` expected by the tests.
// Generic overload for arbitrary range-like types.
template <typename RangeA, typename RangeB>
inline List_comparison sublist(const RangeA& a, const RangeB& b) {
    return classify(a, b);
}

 // Overload for brace-initialized lists like `{}` and `{1, 2, 3}`.
inline List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) {
    return classify(a, b);
}

}  // namespace sublist
