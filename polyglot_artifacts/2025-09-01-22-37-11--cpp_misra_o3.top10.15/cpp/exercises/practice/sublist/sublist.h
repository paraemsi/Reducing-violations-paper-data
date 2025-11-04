#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <initializer_list>

namespace sublist {

/*
 * Relationship between two lists.
 */
enum class comparison_result
{
    equal,      // lists are identical
    sublist,    // first list is contained within the second
    superlist,  // first list contains the second
    unequal     // none of the above
};

using List_comparison = comparison_result;

/*
 * Determine whether `small` appears as a contiguous subsequence of `big`.
 */
template <typename T>
constexpr bool is_subsequence(const std::vector<T>& small, const std::vector<T>& big)
{
    if (small.empty())
    {
        return true;
    }

    if (small.size() > big.size())
    {
        return false;
    }

    for (std::size_t i{0U}; i <= (big.size() - small.size()); ++i)
    {
        bool match{true};
        for (std::size_t j{0U}; j < small.size(); ++j)
        {
            if (big[(i + j)] != small[j])
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

/*
 * Compare two lists and classify their relationship.
 */
template <typename T>
constexpr comparison_result compare(const std::vector<T>& list_a, const std::vector<T>& list_b)
{
    if (list_a == list_b)
    {
        return comparison_result::equal;
    }

    if (list_a.size() < list_b.size())
    {
        if (is_subsequence(list_a, list_b))
        {
            return comparison_result::sublist;
        }
        return comparison_result::unequal;
    }

    if (list_a.size() > list_b.size())
    {
        if (is_subsequence(list_b, list_a))
        {
            return comparison_result::superlist;
        }
        return comparison_result::unequal;
    }

    return comparison_result::unequal;
}

/*
 * Public wrapper expected by the test suite. Accepts std::initializer_list
 * to allow calls such as sublist::sublist({1, 2, 3}, {1, 2, 3}).
 */
template <typename T>
constexpr List_comparison sublist(std::initializer_list<T> list_a,
                                  std::initializer_list<T> list_b)
{
    const std::vector<T> vec_a{list_a};
    const std::vector<T> vec_b{list_b};
    return compare(vec_a, vec_b);
}

/*
 * Overload that forwards to the main algorithm when std::vector is provided.
 */
template <typename T>
constexpr List_comparison sublist(const std::vector<T>& list_a,
                                  const std::vector<T>& list_b)
{
    return compare(list_a, list_b);
}

} // namespace sublist
