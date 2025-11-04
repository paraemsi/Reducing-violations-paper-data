#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace sublist {

/*
 * The possible relationships between two lists.
 * Using std::uint8_t as the underlying type satisfies the fixed-width rule.
 */
enum class List_comparison : std::uint8_t
{
    equal,
    sublist,
    superlist,
    unequal
};

/*
 * Return true when `small` appears as a contiguous subsequence inside `big`.
 * The implementation relies on std::search for clarity and efficiency.
 */
template <typename T>
[[nodiscard]] inline auto is_subsequence(const std::vector<T>& small,
                                         const std::vector<T>& big) -> bool
{
    if (small.empty())
    {
        return true;
    }

    auto it = std::search(big.cbegin(), big.cend(), small.cbegin(), small.cend());
    return (it != big.cend());
}

/*
 * Classify the relationship between list_a and list_b.
 */
template <typename T>
[[nodiscard]] inline auto sublist(const std::vector<T>& list_a,
                                  const std::vector<T>& list_b) -> List_comparison
{
    if (list_a == list_b)
    {
        return List_comparison::equal;
    }

    const bool a_contains_b { is_subsequence(list_b, list_a) };
    const bool b_contains_a { is_subsequence(list_a, list_b) };

    if (a_contains_b && (!b_contains_a))
    {
        return List_comparison::superlist;
    }

    if (b_contains_a && (!a_contains_b))
    {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
