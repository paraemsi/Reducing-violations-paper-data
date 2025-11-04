#pragma once

#include <algorithm>
#include <initializer_list>
#include <vector>

namespace sublist {

// Comparison categories between two lists.
enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

// Returns true if 'haystack' contains 'needle' as a contiguous subsequence.
template <typename T>
inline bool contains_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle) {
    if (needle.empty()) {
        return true;
    }
    if (needle.size() > haystack.size()) {
        return false;
    }
    auto it = std::search(haystack.begin(), haystack.end(),
                          needle.begin(), needle.end());
    return it != haystack.end();
}

 // Classify the relationship between lists 'a' and 'b' for int vectors.
List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b);
inline List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) {
    return sublist(std::vector<int>(a), std::vector<int>(b));
}

}  // namespace sublist
