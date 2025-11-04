#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>
#include <initializer_list>

namespace sublist {

enum class Comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

using List_comparison = Comparison;

template <typename Container>
inline bool is_subsequence(const Container& haystack, const Container& needle)
{
    if (needle.empty())
    {
        return true;
    }

    if ((haystack.size() < needle.size()))
    {
        return false;
    }

    const auto it = std::search(std::begin(haystack), std::end(haystack),
                                std::begin(needle), std::end(needle));
    return (it != std::end(haystack));
}

template <typename Container>
inline Comparison compare(const Container& a, const Container& b)
{
    const bool sizes_equal = (a.size() == b.size());
    if (sizes_equal)
    {
        const bool elements_equal = std::equal(std::begin(a), std::end(a),
                                               std::begin(b));
        if (elements_equal)
        {
            return Comparison::equal;
        }
        else
        {
            return Comparison::unequal;
        }
    }

    if ((a.size() > b.size()))
    {
        if (is_subsequence(a, b))
        {
            return Comparison::superlist;
        }
        else
        {
            return Comparison::unequal;
        }
    }
    else
    {
        if (is_subsequence(b, a))
        {
            return Comparison::sublist;
        }
        else
        {
            return Comparison::unequal;
        }
    }
}

inline List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b)
{
    return compare(a, b);
}

inline List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b)
{
    const std::vector<std::int32_t> va(a);
    const std::vector<std::int32_t> vb(b);
    return sublist(va, vb);
}

inline Comparison classify(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b)
{
    return compare(a, b);
}

}  // namespace sublist
