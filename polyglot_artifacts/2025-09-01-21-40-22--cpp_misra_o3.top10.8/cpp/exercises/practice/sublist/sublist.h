#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace sublist {

// Fixed-width integer type compliant with MISRA
using Int      = std::int32_t;
using IntList  = std::vector<Int>;

// Public enumeration expected by the tests
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

// Internal alias keeps existing implementation code unchanged
using Comparison = List_comparison;

// Function demanded by the test-suite
auto sublist(const IntList& listA, const IntList& listB) -> List_comparison;

namespace detail
{
template <typename T>
auto contains(const std::vector<T>& big, const std::vector<T>& small) -> bool
{
    if(small.empty())
    {
        return true;
    }

    if(big.size() < small.size())
    {
        return false;
    }

    const std::size_t limit{(big.size() - small.size()) + static_cast<std::size_t>(1U)};
    for(std::size_t i{0U}; i < limit; ++i)
    {
        bool match{true};
        for(std::size_t j{0U}; j < small.size(); ++j)
        {
            if(!(big[i + j] == small[j]))
            {
                match = false;
                break;
            }
        }
        if(match)
        {
            return true;
        }
    }
    return false;
}
} // namespace detail

template <typename T>
auto compare(const std::vector<T>& listA, const std::vector<T>& listB) -> Comparison
{
    if(listA == listB)
    {
        return Comparison::equal;
    }

    if(detail::contains(listA, listB))
    {
        return Comparison::superlist;
    }

    if(detail::contains(listB, listA))
    {
        return Comparison::sublist;
    }

    return Comparison::unequal;
}

}  // namespace sublist
