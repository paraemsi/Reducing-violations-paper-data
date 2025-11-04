#pragma once

#include <algorithm>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <initializer_list>

namespace sublist {

enum class Comparison
{
    Equal,
    Sublist,
    Superlist,
    Unequal
};

template <typename T>
inline Comparison compare(std::vector<T> const& list_a, std::vector<T> const& list_b)
{
    if ((list_a.size() == list_b.size()) && (std::equal(list_a.begin(), list_a.end(), list_b.begin())))
    {
        return Comparison::Equal;
    }

    if (list_a.empty())
    {
        return (list_b.empty()) ? Comparison::Equal : Comparison::Sublist;
    }

    if (list_b.empty())
    {
        return Comparison::Superlist;
    }

    if ((list_a.size() < list_b.size()) &&
        (std::search(list_b.begin(), list_b.end(), list_a.begin(), list_a.end()) != list_b.end()))
    {
        return Comparison::Sublist;
    }

    if ((list_a.size() > list_b.size()) &&
        (std::search(list_a.begin(), list_a.end(), list_b.begin(), list_b.end()) != list_a.end()))
    {
        return Comparison::Superlist;
    }

    return Comparison::Unequal;
}

/*----------------------------------------------------------------------------*/
/* Public API expected by the exercise test suite                             */
/*----------------------------------------------------------------------------*/

/* Enumeration with the exact name and enumerators required by the tests.     */
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

/* Helper to translate between internal Comparison and public List_comparison */
inline constexpr List_comparison to_public(Comparison const internal) noexcept
{
    switch (internal)
    {
        case Comparison::Equal:      return List_comparison::equal;
        case Comparison::Sublist:    return List_comparison::sublist;
        case Comparison::Superlist:  return List_comparison::superlist;
        default:                     return List_comparison::unequal;
    }
}

/* Vector overload ---------------------------------------------------------- */
template <typename T>
inline List_comparison sublist(std::vector<T> const& list_a,
                               std::vector<T> const& list_b)
{
    return to_public(compare(list_a, list_b));
}

/* Initializer-list overload reinstated to satisfy test calls that pass
   braced-initializer lists directly, e.g. `sublist::sublist({}, {})`.        */
template <typename T>
inline List_comparison sublist(std::initializer_list<T> list_a,
                               std::initializer_list<T> list_b)
{
    /* Convert to vectors and delegate to the primary overload. */
    return sublist(std::vector<T>(list_a), std::vector<T>(list_b));
}

}  // namespace sublist
