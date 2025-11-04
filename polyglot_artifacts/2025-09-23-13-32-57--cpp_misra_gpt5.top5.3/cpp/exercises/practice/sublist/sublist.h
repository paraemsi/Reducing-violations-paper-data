#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace sublist {

// Relationship between two lists.
enum class List_comparison : std::uint8_t {
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
inline bool contains_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle) noexcept
{
    using size_type = typename std::vector<T>::size_type;

    if ((needle.size() == static_cast<size_type>(0U))) {
        return true;
    }

    if ((haystack.size() < needle.size())) {
        return false;
    }

    const size_type last_start = (haystack.size() - needle.size());

    for (size_type i = static_cast<size_type>(0U); i <= last_start; ++i) {
        bool match = true;

        for (size_type j = static_cast<size_type>(0U); j < needle.size(); ++j) {
            if (!((haystack[(i + j)]) == needle[j])) {
                match = false;
                break;
            }
        }

        if (match) {
            return true;
        }
    }

    return false;
}

template <typename T>
inline List_comparison compare(const std::vector<T>& a, const std::vector<T>& b) noexcept
{
    if ((a.size() == b.size())) {
        if (std::equal(a.cbegin(), a.cend(), b.cbegin())) {
            return List_comparison::equal;
        } else {
            return List_comparison::unequal;
        }
    } else if ((a.size() > b.size())) {
        if (contains_subsequence(a, b)) {
            return List_comparison::superlist;
        } else {
            return List_comparison::unequal;
        }
    } else {
        if (contains_subsequence(b, a)) {
            return List_comparison::sublist;
        } else {
            return List_comparison::unequal;
        }
    }
    return List_comparison::unequal;
}

template <typename T>
inline List_comparison classify(const std::vector<T>& a, const std::vector<T>& b) noexcept
{
    return compare(a, b);
}

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept;

}  // namespace sublist
