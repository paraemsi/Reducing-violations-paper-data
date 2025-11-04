#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace sublist {

/*
 * Enumeration describing the relation between two lists.
 */
enum class List_comparison : std::uint8_t
{
    equal,      // Lists are identical
    sublist,    // First list is contained within the second
    superlist,  // First list contains the second
    unequal     // None of the above
};

using list_t = std::vector<std::int32_t>;

/*
 * Generic classification template allowing any element type that is
 * equality-comparable.  This template is defined inline to avoid the
 * need for a separate translation unit and to support vectors whose
 * element type differs from list_t (e.g. std::vector<int> used by the
 * unit tests).
 */
template <typename T>
inline List_comparison sublist(const std::vector<T>& listA,
                               const std::vector<T>& listB)
{
    if (listA == listB)
    {
        return List_comparison::equal;
    }

    const std::size_t sizeA = listA.size();
    const std::size_t sizeB = listB.size();

    if (sizeA < sizeB)
    {
        if (std::search(listB.begin(), listB.end(),
                        listA.begin(), listA.end()) != listB.end())
        {
            return List_comparison::sublist;
        }
    }
    else if (sizeA > sizeB)
    {
        if (std::search(listA.begin(), listA.end(),
                        listB.begin(), listB.end()) != listA.end())
        {
            return List_comparison::superlist;
        }
    }

    return List_comparison::unequal;
}

/*
 * Classify the relation between listA and listB when the element type
 * complies with MISRA by using the fixed-width signed integer alias
 * list_t.  Implemented in sublist.cpp.
 */
List_comparison sublist(const list_t& listA, const list_t& listB);

}  // namespace sublist
