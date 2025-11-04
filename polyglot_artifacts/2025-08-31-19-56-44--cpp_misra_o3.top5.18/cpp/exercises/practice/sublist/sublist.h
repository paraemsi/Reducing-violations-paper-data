#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include <initializer_list>

namespace sublist {

/* Enumeration describing the relationship between two lists. */
enum class List_comparison : std::uint8_t {
    equal,
    sublist,
    superlist,
    unequal
};

/*
 * Determine the relationship between listA and listB.
 *
 * Returns:
 *   result::equal      – lists contain the same elements in the same order
 *   result::sublist    – listA is a (contiguous) sub-sequence of listB
 *   result::superlist  – listA contains listB as a (contiguous) sub-sequence
 *   result::unequal    – none of the above
 */
template <typename T>
inline auto sublist(const std::vector<T>& listA,
                    const std::vector<T>& listB) -> List_comparison
{
    if((listA == listB))
    {
        return List_comparison::equal;
    }

    if((listA.size()) < (listB.size()))
    {
        if((std::search(listB.cbegin(),
                        listB.cend(),
                        listA.cbegin(),
                        listA.cend())) != listB.cend())
        {
            return List_comparison::sublist;
        }

        return List_comparison::unequal;
    }

    if((listA.size()) > (listB.size()))
    {
        if((std::search(listA.cbegin(),
                        listA.cend(),
                        listB.cbegin(),
                        listB.cend())) != listA.cend())
        {
            return List_comparison::superlist;
        }

        return List_comparison::unequal;
    }

    /* Sizes are equal but contents differ. */
    return List_comparison::unequal;
}

/* Convenience overloads for the common Exercism test-cases that operate on
 * sequences of 32-bit signed integers.  These overloads also allow calls
 * with empty brace-initialisers – e.g. sublist::sublist({}, {}) – for which
 * template argument deduction would otherwise fail.
 */
inline auto sublist(const std::vector<std::int32_t>& listA,
                    const std::vector<std::int32_t>& listB) -> List_comparison
{
    return sublist<std::int32_t>(listA, listB);
}

inline auto sublist(std::initializer_list<std::int32_t> listA,
                    std::initializer_list<std::int32_t> listB) -> List_comparison
{
    const std::vector<std::int32_t> vecA(listA);
    const std::vector<std::int32_t> vecB(listB);
    return sublist<std::int32_t>(vecA, vecB);
}

/* Generic overload kept for arbitrary element types. */
template <typename T>
inline auto sublist(std::initializer_list<T> listA,
                    std::initializer_list<T> listB) -> List_comparison
{
    const std::vector<T> vecA(listA);
    const std::vector<T> vecB(listB);
    return sublist(vecA, vecB);
}

}  // namespace sublist
