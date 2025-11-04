#pragma once

#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };

using relation = List_comparison;

template <typename T>
inline bool is_subrange(const std::vector<T>& small, const std::vector<T>& big)
{
    if ((small.empty()) == true)
    {
        return true;
    }

    if ((small.size()) > (big.size()))
    {
        return false;
    }

    typename std::vector<T>::const_iterator it = std::search(big.begin(), big.end(), small.begin(), small.end());
    return (it != big.end());
}

template <typename T>
inline List_comparison compare(const std::vector<T>& a, const std::vector<T>& b)
{
    if ((a.size() == b.size()) && (std::equal(a.begin(), a.end(), b.begin()) == true))
    {
        return List_comparison::equal;
    }
    else if ((a.size() < b.size()) && (is_subrange(a, b) == true))
    {
        return List_comparison::sublist;
    }
    else if ((a.size() > b.size()) && (is_subrange(b, a) == true))
    {
        return List_comparison::superlist;
    }
    else
    {
        return List_comparison::unequal;
    }
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b)
{
    return compare(a, b);
}

template <typename T>
inline List_comparison sublist(std::initializer_list<T> a, std::initializer_list<T> b)
{
    const std::vector<T> va(a);
    const std::vector<T> vb(b);
    return compare(va, vb);
}

inline List_comparison sublist(std::initializer_list<std::int64_t> a, std::initializer_list<std::int64_t> b)
{
    const std::vector<std::int64_t> va(a);
    const std::vector<std::int64_t> vb(b);
    return compare(va, vb);
}

}  // namespace sublist
