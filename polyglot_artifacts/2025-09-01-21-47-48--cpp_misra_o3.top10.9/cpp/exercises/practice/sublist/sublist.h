#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>

namespace sublist {

enum class List_comparison : std::uint8_t
{
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
auto is_subvector(const std::vector<T>& haystack,
                  const std::vector<T>& needle) -> bool
{
    if (needle.empty())
    {
        return true;
    }

    if (needle.size() > haystack.size())
    {
        return false;
    }

    for (std::size_t i {0U}; i <= (haystack.size() - needle.size()); ++i)
    {
        bool match {true};
        for (std::size_t j {0U}; j < needle.size(); ++j)
        {
            if (!(haystack.at(i + j) == needle.at(j)))
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            return true;
        }
    }

    return false;
}

template <typename T>
auto classify(const std::vector<T>& list_a,
              const std::vector<T>& list_b) -> List_comparison
{
    const bool are_equal {(list_a == list_b)};
    if (are_equal)
    {
        return List_comparison::equal;
    }

    if (is_subvector(list_b, list_a))
    {
        return List_comparison::sublist;
    }

    if (is_subvector(list_a, list_b))
    {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

template <typename T>
auto sublist(const std::vector<T>& list_a,
             const std::vector<T>& list_b) -> List_comparison
{
    return classify(list_a, list_b);
}

}  // namespace sublist
