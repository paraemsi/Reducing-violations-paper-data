#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include <initializer_list>

namespace sublist {

enum class relation : std::uint8_t { equal, sublist, superlist, unequal };
using comparison = relation;
using result = relation;
using List_comparison = relation;

template <typename T>
inline bool is_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle)
{
    if ((needle.empty())) {
        return true;
    } else {
        const typename std::vector<T>::const_iterator it =
            std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
        return ((it != haystack.cend()));
    }
}

template <typename T>
inline relation classify(const std::vector<T>& a, const std::vector<T>& b)
{
    if ((a == b)) {
        return relation::equal;
    } else if ((is_subsequence(a, b))) {
        return relation::superlist;
    } else if ((is_subsequence(b, a))) {
        return relation::sublist;
    } else {
        return relation::unequal;
    }
}

template <typename T>
inline relation check(const std::vector<T>& a, const std::vector<T>& b)
{
    return classify(a, b);
}

template <typename T>
inline relation check_lists(const std::vector<T>& a, const std::vector<T>& b)
{
    return classify(a, b);
}

// Templated convenience function to match vectors of any element type
template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b) noexcept
{
    return classify(a, b);
}

// Non-template convenience overload for fixed-width integer lists
comparison check(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) noexcept;

// Function expected by tests
List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) noexcept;
// Overload to support brace-initializer calls in tests
List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b) noexcept;

}  // namespace sublist
