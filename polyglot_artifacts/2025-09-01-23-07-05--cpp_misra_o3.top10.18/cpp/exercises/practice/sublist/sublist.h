#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>

namespace sublist {

enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

namespace detail
{

template <typename T>
inline auto is_subsequence(const std::vector<T>& small,
                           const std::vector<T>& big) -> bool
{
    if (small.empty())
    {
        return true;
    }

    auto result_iter = std::search(big.begin(), big.end(),
                                   small.begin(), small.end());
    return (result_iter != big.end());
}

template <typename T>
inline auto compare_lists(const std::vector<T>& list_a,
                          const std::vector<T>& list_b) -> List_comparison
{
    if (list_a == list_b)
    {
        return List_comparison::equal;
    }

    if (is_subsequence(list_a, list_b))
    {
        return List_comparison::sublist;
    }

    if (is_subsequence(list_b, list_a))
    {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

} // namespace detail

auto sublist(const std::vector<std::int32_t>& list_a,
             const std::vector<std::int32_t>& list_b) -> List_comparison;

} // namespace sublist
