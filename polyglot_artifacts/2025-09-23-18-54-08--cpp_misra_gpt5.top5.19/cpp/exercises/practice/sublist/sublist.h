#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace sublist {

enum class List_comparison : std::uint8_t
{
    equal = 0U,
    sublist = 1U,
    superlist = 2U,
    unequal = 3U
};

using comparison = List_comparison;

template <typename T>
inline bool is_subsequence(const std::vector<T>& small, const std::vector<T>& large) noexcept
{
    if (small.empty())
    {
        return true;
    }

    if ((small.size() > large.size()))
    {
        return false;
    }

    const auto it = std::search(large.cbegin(), large.cend(), small.cbegin(), small.cend());
    return (it != large.cend());
}

template <typename T>
inline List_comparison compare(const std::vector<T>& a, const std::vector<T>& b) noexcept
{
    if ((a == b))
    {
        return List_comparison::equal;
    }

    if (is_subsequence(b, a))
    {
        return List_comparison::superlist;
    }

    if (is_subsequence(a, b))
    {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

inline List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) noexcept
{
    return compare(a, b);
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b) noexcept
{
    return compare(a, b);
}

template <typename T>
inline List_comparison check(const std::vector<T>& a, const std::vector<T>& b) noexcept
{
    return compare(a, b);
}

template <typename T>
inline List_comparison classify(const std::vector<T>& a, const std::vector<T>& b) noexcept
{
    return compare(a, b);
}

}  // namespace sublist
