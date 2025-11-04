#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <initializer_list>

namespace sublist {

enum class Comparison : std::uint8_t {
    equal = 0U,
    sublist = 1U,
    superlist = 2U,
    unequal = 3U
};
using List_comparison = Comparison;

template <typename It1, typename It2>
inline bool contains_subsequence(It1 first, It1 last, It2 sub_first, It2 sub_last) noexcept
{
    if ((sub_first == sub_last)) {
        return true;
    }
    return (std::search(first, last, sub_first, sub_last) != last);
}

template <typename It1, typename It2>
inline bool ranges_equal(It1 first1, It1 last1, It2 first2, It2 last2) noexcept
{
    while ((first1 != last1) && (first2 != last2)) {
        if (!((*first1) == (*first2))) {
            return false;
        }
        // continue
        ++first1;
        ++first2;
    }
    return ((first1 == last1) && (first2 == last2));
}

template <typename SeqA, typename SeqB>
inline Comparison check(const SeqA& a, const SeqB& b) noexcept
{
    const auto a_first = std::begin(a);
    const auto a_last = std::end(a);
    const auto b_first = std::begin(b);
    const auto b_last = std::end(b);

    if ((ranges_equal(a_first, a_last, b_first, b_last))) {
        return Comparison::equal;
    } else if ((contains_subsequence(a_first, a_last, b_first, b_last))) {
        return Comparison::superlist;
    } else if ((contains_subsequence(b_first, b_last, a_first, a_last))) {
        return Comparison::sublist;
    } else {
        return Comparison::unequal;
    }
}

// Optional alias often used in some codebases.
template <typename SeqA, typename SeqB>
inline List_comparison compare(const SeqA& a, const SeqB& b) noexcept
{
    return (check(a, b));
}

template <typename SeqA, typename SeqB>
inline List_comparison sublist(const SeqA& a, const SeqB& b) noexcept
{
    return (check(a, b));
}

inline List_comparison sublist(std::initializer_list<std::int32_t> a,
                               std::initializer_list<std::int32_t> b) noexcept
{
    return (check(a, b));
}

}  // namespace sublist
