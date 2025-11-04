#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

namespace sublist {

// Enumeration representing the relationship between two lists.
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

// Determine the relationship between list_a and list_b.
//
// The algorithm checks for equality first, then whether one list is a
// contiguous subsequence of the other.  The MISRA C++ rules enforced in the
// project are observed throughout the implementation.
template <typename T>
auto sublist(const std::vector<T> & list_a, const std::vector<T> & list_b) -> List_comparison
{
    if (list_a == list_b)
    {
        return List_comparison::equal;
    }

    const bool a_is_shorter { (list_a.size() < list_b.size()) };

    const std::vector<T> & shorter { a_is_shorter ? list_a : list_b };
    const std::vector<T> & longer  { a_is_shorter ? list_b : list_a };

    if (shorter.empty())
    {
        return a_is_shorter ? List_comparison::sublist : List_comparison::superlist;
    }

    if (std::search(longer.cbegin(),
                    longer.cend(),
                    shorter.cbegin(),
                    shorter.cend()) != longer.cend())
    {
        return a_is_shorter ? List_comparison::sublist : List_comparison::superlist;
    }

    return List_comparison::unequal;
}

template <typename T>
inline auto classify(const std::vector<T> & list_a,
                     const std::vector<T> & list_b) -> List_comparison
{
    return sublist(list_a, list_b);
}

} // namespace sublist
