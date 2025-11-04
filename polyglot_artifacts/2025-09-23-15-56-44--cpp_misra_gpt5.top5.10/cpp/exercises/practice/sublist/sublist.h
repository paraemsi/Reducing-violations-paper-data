#pragma once

#include <algorithm>
#include <cstdint>
#include <initializer_list>

namespace sublist {

enum class List_comparison : std::uint8_t
{
    equal = 0U,
    superlist = 1U,
    sublist = 2U,
    unequal = 3U
};

template <typename Iterable>
inline bool contains(const Iterable& haystack, const Iterable& needle)
{
    if ((needle.size()) == 0U)
    {
        return true;
    }

    if ((haystack.size()) < (needle.size()))
    {
        return false;
    }

    auto it = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end());
    return (it != haystack.end());
}

template <typename Iterable>
inline List_comparison check(const Iterable& a, const Iterable& b)
{
    if ((a.size()) == (b.size()))
    {
        if (std::equal(a.begin(), a.end(), b.begin()))
        {
            return List_comparison::equal;
        }
    }

    if (contains(a, b))
    {
        return List_comparison::superlist;
    }

    if (contains(b, a))
    {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

template <typename Iterable>
inline List_comparison classify(const Iterable& a, const Iterable& b)
{
    return check(a, b);
}

template <typename Iterable>
inline List_comparison sublist(const Iterable& a, const Iterable& b)
{
    return check(a, b);
}

template <typename T>
inline List_comparison sublist(std::initializer_list<T> a, std::initializer_list<T> b)
{
    return check(a, b);
}

// Overload to support calls with empty braced-initializers {}, which cannot deduce T
inline List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b)
{
    return check(a, b);
}

}  // namespace sublist
