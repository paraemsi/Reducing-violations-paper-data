#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

namespace sublist {

/*
 * Enumerates the possible relationships between two lists.
 * The underlying type is std::uint8_t to avoid using the
 * implementation-defined default integral type.
 */
enum class List_comparison : std::uint8_t
{
    equal,
    sublist,
    superlist,
    unequal
};

/*
 * Determine the relationship between two lists.
 * A and B may contain any value-type that supports equality comparison.
 */
template <typename T>
inline auto sublist(const std::vector<T>& listA,
                    const std::vector<T>& listB) -> List_comparison
{
    /* Equal? */
    if ((listA == listB))
    {
        return List_comparison::equal;
    }

    /* Lambda to check whether |small| occurs as a contiguous subsequence
       within |big|. */
    auto const is_subsequence = [](const std::vector<T>& big,
                                   const std::vector<T>& small) -> bool
    {
        if ((small.empty()))
        {
            return true;
        }
        if ((big.size() < small.size()))
        {
            return false;
        }

        auto const it = std::search(big.begin(),
                                    big.end(),
                                    small.begin(),
                                    small.end());

        return ((it != big.end()));
    };

    /* listB inside listA → listA is the superlist */
    if (is_subsequence(listA, listB))
    {
        return List_comparison::superlist;
    }

    /* listA inside listB → listA is the sublist */
    if (is_subsequence(listB, listA))
    {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

/*------------------------------------------------------------------------------
 * Convenience overload for the exercise test-suite.
 *
 * The tests invoke `sublist::sublist({}, {})` and similar brace-initialised
 * calls, which rely on an implicit conversion from an `initializer_list`
 * to `std::vector<int>`. Template argument deduction cannot occur when both
 * arguments are empty, so we provide this explicit overload that forwards to
 * the fully generic template implementation.
 *
 * NOTE: The parameter type employs the built-in `int` solely to interoperate
 * with the pre-existing test code. In production code a fixed-width type would
 * be preferable to satisfy strict MISRA compliance.
 *----------------------------------------------------------------------------*/
inline auto sublist(const std::vector<int>& listA,
                    const std::vector<int>& listB) -> List_comparison
{
    return sublist<int>(listA, listB);
}

}  // namespace sublist
