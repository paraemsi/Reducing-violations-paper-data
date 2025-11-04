#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>

namespace sublist {

enum class List_comparison : std::uint8_t { equal, sublist, superlist, unequal };

template <typename T>
inline auto is_subsequence(const std::vector<T>& needle, const std::vector<T>& haystack) -> bool
{
    if (needle.empty()) {
        return true;
    }

    if (needle.size() > haystack.size()) {
        return false;
    }

    const auto it = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
    return (it != haystack.cend());
}

template <typename T>
inline auto sublist(const std::vector<T>& a, const std::vector<T>& b) -> List_comparison
{
    if ((a.size() == b.size()) && (std::equal(a.cbegin(), a.cend(), b.cbegin()))) {
        return (List_comparison::equal);
    }

    if (is_subsequence(a, b)) {
        return (List_comparison::sublist);
    }

    if (is_subsequence(b, a)) {
        return (List_comparison::superlist);
    }

    return (List_comparison::unequal);
}

inline auto sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) -> List_comparison
{
    return ::sublist::sublist<std::int32_t>(a, b);
}

}  // namespace sublist
