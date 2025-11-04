#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iterator>
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
inline bool is_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle)
{
    if ((needle.empty()))
    {
        return true;
    }
    else
    {
        const typename std::vector<T>::const_iterator it = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
        return (it != haystack.cend());
    }
}

template <typename T>
inline List_comparison check(const std::vector<T>& a, const std::vector<T>& b)
{
    if ((a == b))
    {
        return List_comparison::equal;
    }

    using size_type = typename std::vector<T>::size_type;
    const size_type a_size = a.size();
    const size_type b_size = b.size();

    if ((a_size < b_size))
    {
        if ((is_subsequence(b, a)))
        {
            return List_comparison::sublist;
        }
        else
        {
            return List_comparison::unequal;
        }
    }
    else if ((a_size > b_size))
    {
        if ((is_subsequence(a, b)))
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
        return List_comparison::unequal;
    }
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b)
{
    return check<T>(a, b);
}

template <typename T>
inline List_comparison sublist(std::initializer_list<T> a, std::initializer_list<T> b)
{
    const std::vector<T> va(a);
    const std::vector<T> vb(b);
    return check<T>(va, vb);
}

// Non-template overload to support empty-brace calls: sublist::sublist({}, {})
inline List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b)
{
    const std::vector<std::int32_t> va(a);
    const std::vector<std::int32_t> vb(b);
    return check<std::int32_t>(va, vb);
}

}  // namespace sublist
