#pragma once

#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdint>

namespace sublist {

enum class List_comparison : std::int8_t
{
    equal,
    sublist,
    superlist,
    unequal
};

namespace detail
{
    template<typename T>
    auto is_subsequence(const std::vector<T>& long_list,
                        const std::vector<T>& short_list) -> bool
    {
        if(short_list.empty())
        {
            return true;
        }

        const auto it = std::search(long_list.cbegin(),
                                    long_list.cend(),
                                    short_list.cbegin(),
                                    short_list.cend());

        return (it != long_list.cend());
    }
} // namespace detail

template<typename T>
auto sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) -> List_comparison
{
    if(list_a == list_b)
    {
        return List_comparison::equal;
    }

    if(detail::is_subsequence(list_a, list_b))
    {
        return List_comparison::superlist;
    }

    if(detail::is_subsequence(list_b, list_a))
    {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
