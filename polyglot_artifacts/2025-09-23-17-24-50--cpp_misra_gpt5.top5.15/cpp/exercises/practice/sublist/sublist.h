#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace sublist {

enum class List_comparison : std::uint8_t
{
    equal,
    superlist,
    sublist,
    unequal
};

template <typename T>
inline bool contains_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle)
{
    if (needle.empty())
    {
        return true;
    }
    else
    {
        if ((haystack.size() < needle.size()))
        {
            return false;
        }
        else
        {
            const typename std::vector<T>::const_iterator it = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
            return (it != haystack.cend());
        }
    }
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b)
{
    if ((a.size() == b.size()))
    {
        if (std::equal(a.cbegin(), a.cend(), b.cbegin()))
        {
            return List_comparison::equal;
        }
        else
        {
            return List_comparison::unequal;
        }
    }
    else if ((a.size() > b.size()))
    {
        if (contains_subsequence(a, b))
        {
            return List_comparison::superlist;
        }
        else
        {
            return List_comparison::unequal;
        }
    }
    else
    {
        if (contains_subsequence(b, a))
        {
            return List_comparison::sublist;
        }
        else
        {
            return List_comparison::unequal;
        }
    }
}
 
inline List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b)
{
    return ::sublist::sublist<std::int32_t>(a, b);
}

}  // namespace sublist
