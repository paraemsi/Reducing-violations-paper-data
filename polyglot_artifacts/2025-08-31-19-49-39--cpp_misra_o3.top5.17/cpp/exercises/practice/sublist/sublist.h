#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>
#include <initializer_list>

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };

/*
 * Determine whether `small` appears as a contiguous subsequence of `large`.
 */
template <typename T>
inline auto is_subsequence(const std::vector<T>& small,
                           const std::vector<T>& large) -> bool
{
    const std::size_t small_size { small.size() };
    const std::size_t large_size { large.size() };

    if(small_size == 0U)
    {
        return true;   /* The empty list is a sub-sequence of every list. */
    }

    if(small_size > large_size)
    {
        return false;
    }

    for(std::size_t start { 0U };
        (start + small_size) <= large_size;
        ++start)
    {
        bool match { true };

        for(std::size_t offset { 0U }; offset < small_size; ++offset)
        {
            if(!(large[start + offset] == small[offset]))
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

/*
 * Classify the relationship between two lists.
 */
template <typename T>
inline auto classify(const std::vector<T>& list_a,
                     const std::vector<T>& list_b) -> List_comparison
{
    if(list_a == list_b)
    {
        return List_comparison::equal;
    }

    if(is_subsequence(list_a, list_b))
    {
        return List_comparison::sublist;
    }

    if(is_subsequence(list_b, list_a))
    {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

template <typename T>
inline auto sublist(const std::vector<T>& list_a,
                    const std::vector<T>& list_b) -> List_comparison
{
    return classify(list_a, list_b);
}

template <typename T>
inline auto sublist(std::initializer_list<T> list_a,
                    std::initializer_list<T> list_b) -> List_comparison
{
    const std::vector<T> vec_a(list_a);
    const std::vector<T> vec_b(list_b);
    return classify(vec_a, vec_b);
}

}  // namespace sublist
