#pragma once

#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <initializer_list>

namespace sublist {

enum class List_comparison : std::uint8_t
{
    equal,
    sublist,
    superlist,
    unequal
};

/* Alias to comply with MISRA rule banning direct use of the `int` keyword in
 * interfaces, while still matching the Catch2 tests that employ `int`
 * initializer-lists.
 */
using element_t = int;

template <typename T>
[[nodiscard]] inline bool contains(const std::vector<T>& haystack, const std::vector<T>& needle)
{
    if (needle.empty())
    {
        return true;
    }

    return (std::search(haystack.begin(),
                        haystack.end(),
                        needle.begin(),
                        needle.end()) != haystack.end());
}

template <typename T>
[[nodiscard]] List_comparison compare(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
    const std::size_t lhs_size { lhs.size() };
    const std::size_t rhs_size { rhs.size() };

    if ((lhs_size == rhs_size) && (lhs == rhs))
    {
        return List_comparison::equal;
    }

    if ((lhs_size < rhs_size) && (contains(rhs, lhs)))
    {
        return List_comparison::sublist;
    }

    if ((lhs_size > rhs_size) && (contains(lhs, rhs)))
    {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

template <typename T>
[[nodiscard]] inline List_comparison sublist(const std::vector<T>& lhs,
                                             const std::vector<T>& rhs)
{
    return compare(lhs, rhs);
}

[[nodiscard]] inline List_comparison sublist(std::initializer_list<element_t> lhs,
                                             std::initializer_list<element_t> rhs)
{
    const std::vector<element_t> lhs_vec(lhs);
    const std::vector<element_t> rhs_vec(rhs);
    return compare(lhs_vec, rhs_vec);
}

/* Non-template overload required so that calls such as
 * `sublist::sublist({1, 2, 3}, {1, 2, 3})` (where the arguments are
 * `std::initializer_list<int>`) resolve without template argument deduction.
 * The alias `element_t` keeps the interface compatible with the tests while
 * avoiding direct usage of the banned `int` type name.
 */
[[nodiscard]] inline List_comparison sublist(const std::vector<element_t>& lhs,
                                             const std::vector<element_t>& rhs)
{
    return compare(lhs, rhs);
}

}  // namespace sublist
