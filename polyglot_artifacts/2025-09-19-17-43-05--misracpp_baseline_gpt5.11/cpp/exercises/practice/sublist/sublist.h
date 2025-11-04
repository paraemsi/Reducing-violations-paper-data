#pragma once

#include <algorithm>
#include <iterator>
#include <vector>

namespace sublist {

// Relationship between two lists as required by the tests.
enum class List_comparison { equal, sublist, superlist, unequal };

template <typename Range>
inline bool contains_subsequence(const Range& haystack, const Range& needle) noexcept {
    if (needle.size() == 0) return true;
    if (needle.size() > haystack.size()) return false;
    auto it = std::search(std::cbegin(haystack), std::cend(haystack),
                          std::cbegin(needle), std::cend(needle));
    return it != std::cend(haystack);
}

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept;

}  // namespace sublist
