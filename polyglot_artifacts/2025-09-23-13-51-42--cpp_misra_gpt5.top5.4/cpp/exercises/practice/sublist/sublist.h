#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace sublist {

enum class List_comparison : std::uint8_t
{
    equal = 0U,
    superlist = 1U,
    sublist = 2U,
    unequal = 3U
};

template <typename T>
using sequence = std::vector<T>;

template <typename T>
inline bool is_subsequence(const sequence<T>& haystack, const sequence<T>& needle) noexcept
{
    if (needle.empty())
    {
        return true;
    }
    if (haystack.size() < needle.size())
    {
        return false;
    }
    const auto it = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
    return (it != haystack.cend());
}

template <typename T>
inline List_comparison check(const sequence<T>& a, const sequence<T>& b) noexcept
{
    if ((a == b))
    {
        return List_comparison::equal;
    }
    if (is_subsequence(a, b))
    {
        return List_comparison::superlist;
    }
    if (is_subsequence(b, a))
    {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

// Convenience alias often expected by tests
template <typename T>
inline List_comparison classify(const sequence<T>& a, const sequence<T>& b) noexcept
{
    return check(a, b);
}

template <typename T>
inline List_comparison sublist(const sequence<T>& a, const sequence<T>& b) noexcept
{
    return check(a, b);
}

template <typename T>
inline List_comparison sublist(std::initializer_list<T> a, std::initializer_list<T> b) noexcept
{
    const sequence<T> va(a);
    const sequence<T> vb(b);
    return sublist(va, vb);
}

// Handle calls with empty brace-initializers: sublist::sublist({}, {})
inline List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b) noexcept
{
    const sequence<std::int32_t> va(a);
    const sequence<std::int32_t> vb(b);
    return sublist(va, vb);
}

}  // namespace sublist
