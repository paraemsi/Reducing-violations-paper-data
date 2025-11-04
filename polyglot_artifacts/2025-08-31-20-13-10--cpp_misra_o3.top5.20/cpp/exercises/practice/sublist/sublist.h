#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include <initializer_list>

namespace sublist {

/*  Result of comparing two lists */
enum class List_comparison : std::uint8_t
{
    equal,      /* lists are identical                     */
    sublist,    /* first  list is contained   in second    */
    superlist,  /* first  list contains        second      */
    unequal     /* no relation                              */
};

/*  Classify the relationship between two lists.
 *  T may be any value type that supports equality comparison.
 *  The implementation is provided here as a function template to
 *  avoid explicitly naming standard integer types, thus complying
 *  with the MISRA C++ rules supplied with the task.
 */
template <typename T>
inline auto sublist(const std::vector<T>& list_a,
                    const std::vector<T>& list_b) -> List_comparison
{
    if (list_a == list_b)
    {
        return List_comparison::equal;
    }

    if (list_a.empty())
    {
        return List_comparison::sublist;
    }

    if (list_b.empty())
    {
        return List_comparison::superlist;
    }

    const auto contains_subsequence =
        [](const std::vector<T>& long_list,
           const std::vector<T>& short_list) -> bool
        {
            const auto it = std::search(long_list.cbegin(), long_list.cend(),
                                        short_list.cbegin(), short_list.cend());
            return (it != long_list.cend());
        };

    if (list_a.size() < list_b.size())
    {
        return (contains_subsequence(list_b, list_a)) ? List_comparison::sublist : List_comparison::unequal;
    }

    if (list_a.size() > list_b.size())
    {
        return (contains_subsequence(list_a, list_b)) ? List_comparison::superlist : List_comparison::unequal;
    }

    return List_comparison::unequal;
}

/*  Overload taking initializer_list literals for convenient calling
 *  forwards to the std::vector<T> version.                                   */
template <typename T>
inline auto sublist(std::initializer_list<T> list_a,
                    std::initializer_list<T> list_b) -> List_comparison
{
    const std::vector<T> vec_a(list_a);
    const std::vector<T> vec_b(list_b);
    return sublist(vec_a, vec_b);
}

} // namespace sublist
