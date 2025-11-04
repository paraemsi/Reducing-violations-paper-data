#pragma once

#include <vector>
#include <algorithm>

namespace sublist {

/*  Relationship between two lists as described in the exercise */
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

/*  Determine the relationship between listA and listB.                     */
template <typename T>
[[nodiscard]] auto sublist(const std::vector<T>& listA,
                           const std::vector<T>& listB) -> List_comparison
{
    if ((listA == listB)) {
        return List_comparison::equal;
    }

    /*  Local helper: checks if ‘big’ contains ‘small’ as contiguous slice   */
    const auto contains_subsequence =
        [](const std::vector<T>& big, const std::vector<T>& small) -> bool
        {
            if (small.empty()) {
                return true;
            }

            return (std::search(big.cbegin(),
                                big.cend(),
                                small.cbegin(),
                                small.cend()) != big.cend());
        };

    if (contains_subsequence(listA, listB)) {
        return List_comparison::superlist;
    }

    if (contains_subsequence(listB, listA)) {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
