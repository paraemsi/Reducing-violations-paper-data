#pragma once

#include <algorithm>
#include <iterator>
#include <initializer_list>

namespace sublist {

enum class comparison { equal, sublist, superlist, unequal };
using relation = comparison;
using List_comparison = comparison;

namespace detail {
template <typename It1, typename It2>
inline bool contains_subsequence(It1 first1, It1 last1, It2 first2, It2 last2) {
    if (first2 == last2) {
        return true;  // empty sequence is contained everywhere
    }
    return std::search(first1, last1, first2, last2) != last1;
}

template <typename Seq1, typename Seq2>
inline comparison compare_impl(const Seq1& a, const Seq2& b) {
    using std::begin;
    using std::end;
    auto a_first = begin(a);
    auto a_last = end(a);
    auto b_first = begin(b);
    auto b_last = end(b);

    const auto a_size = std::distance(a_first, a_last);
    const auto b_size = std::distance(b_first, b_last);

    if (a_size == b_size && std::equal(a_first, a_last, b_first)) {
        return comparison::equal;
    }
    if (contains_subsequence(a_first, a_last, b_first, b_last)) {
        return comparison::superlist;
    }
    if (contains_subsequence(b_first, b_last, a_first, a_last)) {
        return comparison::sublist;
    }
    return comparison::unequal;
}
}  // namespace detail

template <typename Seq1, typename Seq2>
inline comparison check(const Seq1& a, const Seq2& b) {
    return detail::compare_impl(a, b);
}

template <typename Seq1, typename Seq2>
inline comparison classify(const Seq1& a, const Seq2& b) {
    return detail::compare_impl(a, b);
}

template <typename Seq1, typename Seq2>
inline comparison sublist(const Seq1& a, const Seq2& b) {
    return detail::compare_impl(a, b);
}

// Overload to support initializer_list arguments used in tests
inline List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) noexcept {
    return detail::compare_impl(a, b);
}

}  // namespace sublist
