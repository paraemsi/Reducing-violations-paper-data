#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

namespace sublist {

enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
[[nodiscard]] auto sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) -> List_comparison
{
    const std::size_t size_a{ list_a.size() };
    const std::size_t size_b{ list_b.size() };

    if ((size_a == size_b) && (std::equal(list_a.cbegin(), list_a.cend(), list_b.cbegin())))
    {
        return List_comparison::equal;
    }

    if (size_a < size_b)
    {
        if ((size_a == static_cast<std::size_t>(0U)) ||
            (std::search(list_b.cbegin(), list_b.cend(), list_a.cbegin(), list_a.cend()) != list_b.cend()))
        {
            return List_comparison::sublist;
        }
    }

    if (size_a > size_b)
    {
        if ((size_b == static_cast<std::size_t>(0U)) ||
            (std::search(list_a.cbegin(), list_a.cend(), list_b.cbegin(), list_b.cend()) != list_a.cend()))
        {
            return List_comparison::superlist;
        }
    }

    return List_comparison::unequal;
}

}  // namespace sublist
