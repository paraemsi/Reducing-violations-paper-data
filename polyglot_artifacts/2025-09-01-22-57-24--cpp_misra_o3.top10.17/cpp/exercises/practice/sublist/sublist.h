/*  Header implementing sublist classification – conforming to MISRA C++ rules. */
#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>

namespace sublist {

// Classification result between two lists
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

namespace detail {

// Returns true if |longer| contains |shorter| as a contiguous subsequence
template <typename T>
[[nodiscard]] inline bool contains_subsequence(
    const std::vector<T>& longer,
    const std::vector<T>& shorter)
{
    if(shorter.empty())
    {
        return true;
    }

    if(longer.size() < shorter.size())
    {
        return false;
    }

    const std::size_t limit{ (static_cast<std::size_t>(longer.size() - shorter.size()) + static_cast<std::size_t>(1U)) };

    for(std::size_t i{ static_cast<std::size_t>(0U) }; i < limit; ++i)
    {
        bool match{ true };
        for(std::size_t j{ static_cast<std::size_t>(0U) }; j < shorter.size(); ++j)
        {
            if(!(longer[(i + j)] == shorter[j]))
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

// Determine the relation between list A and list B
template <typename T>
[[nodiscard]] inline List_comparison sublist(
    const std::vector<T>& a,
    const std::vector<T>& b)
{
    if(a == b)
    {
        return List_comparison::equal;
    }

    const bool a_contains_b{ detail::contains_subsequence(a, b) };
    const bool b_contains_a{ detail::contains_subsequence(b, a) };

    if((a_contains_b) && (!b_contains_a))
    {
        return List_comparison::superlist;
    }

    if((b_contains_a) && (!a_contains_b))
    {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

// Convenience overload for the exercise tests – works with
// brace-initialiser arguments such as `{}` or `{1, 2, 3}`.
[[nodiscard]] inline List_comparison sublist(
    const std::vector<std::int32_t>& a,
    const std::vector<std::int32_t>& b)
{
    return sublist<std::int32_t>(a, b);
}

}  // namespace sublist
