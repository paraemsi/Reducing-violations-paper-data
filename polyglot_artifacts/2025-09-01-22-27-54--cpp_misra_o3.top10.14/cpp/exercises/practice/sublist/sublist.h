#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace sublist {

/*-------------------------------------------------------------------------*/
/*  Result enumeration                                                     */
/*-------------------------------------------------------------------------*/
enum class List_comparison : std::uint8_t
{
    equal,
    sublist,
    superlist,
    unequal
};

/*-------------------------------------------------------------------------*/
/*  Internal helper – check for contiguous sub-list                        */
/*-------------------------------------------------------------------------*/
template <typename T>
constexpr bool is_contiguous_sublist(const std::vector<T>& bigger,
                                     const std::vector<T>& smaller) noexcept
{
    if (smaller.empty())
    {
        return true;
    }

    if (bigger.size() < smaller.size())
    {
        return false;
    }

    const std::size_t limit { (bigger.size() - smaller.size()) + static_cast<std::size_t>(1U) };

    for (std::size_t i { 0U }; i < limit; ++i)
    {
        bool match { true };

        for (std::size_t j { 0U }; j < smaller.size(); ++j)
        {
            if (!(bigger[(i + j)] == smaller[j]))
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            return true;
        }
    }

    return false;
}

/*-------------------------------------------------------------------------*/
/*  Public API – compare two lists                                         */
/*-------------------------------------------------------------------------*/
template <typename T>
constexpr List_comparison sublist(const std::vector<T>& listA,
                                  const std::vector<T>& listB) noexcept
{
    if (listA == listB)
    {
        return List_comparison::equal;
    }

    if (is_contiguous_sublist(listA, listB))
    {
        return List_comparison::superlist;
    }

    if (is_contiguous_sublist(listB, listA))
    {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
