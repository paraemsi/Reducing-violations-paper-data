#pragma once

#include <algorithm>
#include <iterator>
#include <vector>

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };

template <typename It1, typename It2>
inline bool contains(It1 first1, It1 last1, It2 first2, It2 last2) {
    if (first2 == last2) {
        // An empty sequence is always a sub-sequence.
        return true;
    }
    return std::search(first1, last1, first2, last2) != last1;
}

template <typename Seq>
inline bool sequence_equal(const Seq& a, const Seq& b) {
    auto a_begin = std::begin(a);
    auto a_end = std::end(a);
    auto b_begin = std::begin(b);
    auto b_end = std::end(b);

    if (std::distance(a_begin, a_end) != std::distance(b_begin, b_end)) {
        return false;
    }
    return std::equal(a_begin, a_end, b_begin, b_end);
}

template <typename Seq>
List_comparison check(const Seq& a, const Seq& b) {
    if (sequence_equal(a, b)) {
        return List_comparison::equal;
    }
    if (contains(std::begin(a), std::end(a), std::begin(b), std::end(b))) {
        return List_comparison::superlist;
    }
    if (contains(std::begin(b), std::end(b), std::begin(a), std::end(a))) {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b);

}  // namespace sublist
