#pragma once

#include <vector>
#include <iterator>
#include <initializer_list>

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };

template <typename SmallSeq, typename BigSeq>
bool is_subsequence(const SmallSeq& small, const BigSeq& big) {
    auto s_begin = std::begin(small);
    auto s_end = std::end(small);
    if (s_begin == s_end) return true;

    auto b_begin = std::begin(big);
    auto b_end = std::end(big);

    for (auto it = b_begin; it != b_end; ++it) {
        auto it_small = s_begin;
        auto it_big = it;
        while (it_small != s_end && it_big != b_end && (*it_big == *it_small)) {
            ++it_small;
            ++it_big;
        }
        if (it_small == s_end) return true;
        if (it_big == b_end) break;
    }
    return false;
}

template <typename ASeq, typename BSeq>
List_comparison check(const ASeq& a, const BSeq& b) {
    const bool a_in_b = is_subsequence(a, b);
    const bool b_in_a = is_subsequence(b, a);
    if (a_in_b && b_in_a) return List_comparison::equal;
    if (b_in_a) return List_comparison::superlist;
    if (a_in_b) return List_comparison::sublist;
    return List_comparison::unequal;
}

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept;
List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) noexcept;

}  // namespace sublist
