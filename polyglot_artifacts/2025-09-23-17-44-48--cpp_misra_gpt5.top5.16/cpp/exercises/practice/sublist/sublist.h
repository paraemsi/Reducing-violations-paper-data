#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace sublist {

enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

namespace detail {
// Helper to check if 'needle' appears as a contiguous sub-sequence in 'haystack'.
template <typename T>
inline bool contains_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle)
{
    if (needle.empty()) {
        return true;
    }

    const std::size_t haystack_size = haystack.size();
    const std::size_t needle_size = needle.size();

    if ((haystack_size < needle_size)) {
        return false;
    }

    const std::size_t limit = (haystack_size - needle_size);
    for (std::size_t i = 0U; (i <= limit); ++i) {
        bool match = true;
        for (std::size_t j = 0U; (j < needle_size); ++j) {
            if (!(haystack[(i + j)] == needle[j])) {
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
}  // namespace detail

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b)
{
    if ((a.size() == b.size()) && (std::equal(a.cbegin(), a.cend(), b.cbegin()))) {
        return List_comparison::equal;
    }

    if (detail::contains_subsequence<T>(a, b)) {
        return List_comparison::superlist;
    }

    if (detail::contains_subsequence<T>(b, a)) {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

// Overload to support brace-initializer calls in tests (std::vector<int>).
List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b);

}  // namespace sublist
