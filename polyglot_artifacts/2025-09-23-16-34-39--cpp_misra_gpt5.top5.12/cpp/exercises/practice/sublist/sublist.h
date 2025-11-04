#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace sublist {

enum class comparison : std::uint8_t { equal, sublist, superlist, unequal };
using List_comparison = comparison;

template <typename T>
inline bool contains_sublist(const std::vector<T>& haystack, const std::vector<T>& needle) noexcept {
    if (needle.empty()) {
        return true;
    } else {
        if (haystack.size() < needle.size()) {
            return false;
        } else {
            auto it = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end());
            return (it != haystack.end());
        }
    }
}

template <typename T>
inline comparison classify(const std::vector<T>& a, const std::vector<T>& b) noexcept {
    if ((a.size() == b.size()) && (a == b)) {
        return comparison::equal;
    } else {
        if (contains_sublist(a, b)) {
            return comparison::superlist;
        } else {
            if (contains_sublist(b, a)) {
                return comparison::sublist;
            } else {
                return comparison::unequal;
            }
        }
    }
}

inline List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) noexcept {
    return classify<std::int32_t>(a, b);
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b) noexcept {
    return classify<T>(a, b);
}

template <typename T>
inline comparison check_lists(const std::vector<T>& a, const std::vector<T>& b) noexcept {
    return classify(a, b);
}

}  // namespace sublist
