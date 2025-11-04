#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>

namespace sublist {

/*  Comparison result for two lists                                                    */
enum class Comparison : std::uint8_t
{
    equal,
    sublist,
    superlist,
    unequal
};

using List_comparison = Comparison;

namespace detail {

/*  Return true if ‘smaller’ occurs as a contiguous subsequence inside ‘bigger’.       */
template <typename T>
auto is_subsequence(const std::vector<T>& bigger,
                    const std::vector<T>& smaller) -> bool
{
    if(smaller.empty())
    {
        return true;
    }

    if(bigger.size() < smaller.size())
    {
        return false;
    }

    auto it = std::search(bigger.cbegin(),
                          bigger.cend(),
                          smaller.cbegin(),
                          smaller.cend());

    return (it != bigger.cend());
}

}   // namespace detail

/*  Compare two lists as per the specification                                         */
template <typename T>
auto compare(const std::vector<T>& lhs,
             const std::vector<T>& rhs) -> Comparison
{
    if(lhs == rhs)
    {
        return Comparison::equal;
    }

    if(detail::is_subsequence(rhs, lhs))
    {
        return Comparison::sublist;
    }

    if(detail::is_subsequence(lhs, rhs))
    {
        return Comparison::superlist;
    }

    return Comparison::unequal;
}

template <typename T>
auto sublist(const std::vector<T>& lhs,
             const std::vector<T>& rhs) -> Comparison
{
    return compare(lhs, rhs);
}

}   // namespace sublist
