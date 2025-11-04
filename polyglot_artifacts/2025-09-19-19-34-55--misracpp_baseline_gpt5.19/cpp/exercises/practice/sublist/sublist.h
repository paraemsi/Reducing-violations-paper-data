#pragma once

#include <algorithm>
#include <vector>

namespace sublist {

// Classification result of comparing two sequences
enum class List_comparison { equal, sublist, superlist, unequal };

template <typename T>
inline bool contains_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle) {
    // An empty needle is always a subsequence
    if (needle.empty()) {
        return true;
    }
    if (needle.size() > haystack.size()) {
        return false;
    }
    return std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end()) != haystack.end();
}

template <typename T>
inline List_comparison check(const std::vector<T>& a, const std::vector<T>& b) {
    if (a == b) {
        return List_comparison::equal;
    }
    if (contains_subsequence(a, b)) {
        return List_comparison::superlist;
    }
    if (contains_subsequence(b, a)) {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept;

}  // namespace sublist
