#pragma once

#include <algorithm>   // for std::search
#include <cstdint>     // fixed-width integer types (MISRA compliant)
#include <vector>      // for std::vector
#include <initializer_list>  // for std::initializer_list

namespace sublist {

/* -------------------------------------------------------------------------- */
/*   Enumeration describing the relationship between two lists (public API)   */
/* -------------------------------------------------------------------------- */
enum class List_comparison : std::uint8_t
{
    equal,      // Lists are identical
    sublist,    // First list is contained within the second
    superlist,  // First list contains the second
    unequal     // No sublist / superlist relationship
};


/* -------------------------------------------------------------------------- */
/*                           Template implementation                          */
/* -------------------------------------------------------------------------- */

// Helper: check whether `small` appears as a contiguous sub-sequence of `big`
template <typename T>
static auto is_sublist(const std::vector<T>& small,
                       const std::vector<T>& big) -> bool
{
    if (small.empty())
    {
        return true;
    }

    const auto it = std::search(big.begin(), big.end(), small.begin(), small.end());
    return (it != big.end());
}

// Public API: determine the relationship between two lists
template <typename T>
auto sublist(const std::vector<T>& listA, const std::vector<T>& listB) -> List_comparison
{
    if (listA == listB)
    {
        return List_comparison::equal;
    }

    if (is_sublist(listA, listB))
    {
        return List_comparison::sublist;
    }

    if (is_sublist(listB, listA))
    {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

// Overload to support brace-initialised lists so that calls like
// `sublist::sublist({1, 2, 3}, {1, 2, 3})` compile without having to
// spell out std::vector explicitly.
template <typename T>
auto sublist(std::initializer_list<T> listA,
             std::initializer_list<T> listB) -> List_comparison
{
    const std::vector<T> vecA(listA);
    const std::vector<T> vecB(listB);
    return sublist(vecA, vecB);
}

}  // namespace sublist
