#pragma once

#include <vector>
#include <cstddef>

namespace sublist {

enum class result { equal, sublist, superlist, unequal };
using List_comparison = result;

namespace detail {
// Return true if `big` contains `small` as a contiguous subsequence.
template <typename T>
inline bool contains_subvector(const std::vector<T>& big,
                               const std::vector<T>& small) {
    if (small.empty()) {
        return true;                 // Empty list is sub-sequence of any list
    }
    if (small.size() > big.size()) {
        return false;
    }

    for (std::size_t i = 0; i + small.size() <= big.size(); ++i) {
        bool match = true;
        for (std::size_t j = 0; j < small.size(); ++j) {
            if (!(big[i + j] == small[j])) {
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

// Determine the relationship of list_a to list_b.
template <typename T>
inline List_comparison sublist(const std::vector<T>& list_a,
                               const std::vector<T>& list_b) {
    if (list_a == list_b) {
        return result::equal;
    }
    if (detail::contains_subvector(list_a, list_b)) {
        return result::superlist;
    }
    if (detail::contains_subvector(list_b, list_a)) {
        return result::sublist;
    }
    return result::unequal;
}

inline List_comparison sublist(const std::vector<int>& list_a,
                               const std::vector<int>& list_b) {
    return sublist<int>(list_a, list_b);
}


}  // namespace sublist
