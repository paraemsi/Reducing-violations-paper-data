#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace sublist {

/*
 * The comparison result between two lists.
 */
enum class Comparison
{
    Equal,      /* both lists contain exactly the same elements            */
    Sublist,    /* first list is contained (as a contiguous slice) in second */
    Superlist,  /* first list contains the second one as a contiguous slice */
    Unequal     /* none of the above                                        */
};

/*
 * Enumeration expected by the exercise tests (snake_case style).
 */
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

/*
 * Convert internal Comparison to externally-visible List_comparison.
 */
constexpr auto to_list_comparison(Comparison cmp) noexcept -> List_comparison
{
    switch(cmp)
    {
        case Comparison::Equal:     { return List_comparison::equal; }
        case Comparison::Sublist:   { return List_comparison::sublist; }
        case Comparison::Superlist: { return List_comparison::superlist; }
        case Comparison::Unequal:   { return List_comparison::unequal; }
    }
    /* Defensive default – should never be reached */
    return List_comparison::unequal;
}

/*
 * Return true if `needle` occurs in `haystack` as a contiguous subsequence.
 */
template <typename T>
[[nodiscard]] auto is_subsequence(const std::vector<T>& needle,
                                  const std::vector<T>& haystack) -> bool
{
    if(needle.empty())
    {
        return true;
    }

    return (std::search(haystack.cbegin(),
                        haystack.cend(),
                        needle.cbegin(),
                        needle.cend()) != haystack.cend());
}

/*
 * Compare two lists according to the exercise specification.
 */
template <typename T>
[[nodiscard]] auto compare(const std::vector<T>& listA,
                           const std::vector<T>& listB) -> Comparison
{
    if(listA == listB)
    {
        return Comparison::Equal;
    }

    if(is_subsequence(listB, listA))
    {
        return Comparison::Superlist;
    }

    if(is_subsequence(listA, listB))
    {
        return Comparison::Sublist;
    }

    return Comparison::Unequal;
}

/*
 * Public API function requested by the tests.
 */
template <typename T>
[[nodiscard]] auto sublist(const std::vector<T>& listA,
                           const std::vector<T>& listB) -> List_comparison
{
    return to_list_comparison(compare(listA, listB));
}

}  // namespace sublist
