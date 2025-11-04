#pragma once

#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };

template <typename Haystack, typename Needle>
inline bool is_subsequence(const Haystack& haystack, const Needle& needle)
{
    const auto it = std::search(std::begin(haystack), std::end(haystack),
                                std::begin(needle), std::end(needle));
    return (it != std::end(haystack));
}

template <typename A, typename B>
inline List_comparison check(const A& a, const B& b)
{
    if (std::equal(std::begin(a), std::end(a), std::begin(b), std::end(b)))
    {
        return List_comparison::equal;
    }

    if (is_subsequence(b, a))
    {
        return List_comparison::sublist;
    }

    if (is_subsequence(a, b))
    {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

inline List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b)
{
    return check(a, b);
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b)
{
    return check(a, b);
}

// Convenience aliases frequently used in exercises/tests.
template <typename A, typename B>
inline List_comparison compare(const A& a, const B& b)
{
    return check(a, b);
}

template <typename A, typename B>
inline List_comparison classify(const A& a, const B& b)
{
    return check(a, b);
}

template <typename A, typename B>
inline List_comparison compare_lists(const A& a, const B& b)
{
    return check(a, b);
}

}  // namespace sublist
