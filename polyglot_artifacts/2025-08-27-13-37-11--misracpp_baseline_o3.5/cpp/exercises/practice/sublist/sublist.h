#pragma once

#include <vector>
#include <algorithm>
#include <iterator>

namespace sublist {

/**
 * Relationship between two lists.
 */
enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

/**
 * Determine the relationship of list A to list B.
 *
 * @tparam T   element type (must be comparable with operator==)
 * @param a    first list
 * @param b    second list
 * @return     List_comparison::equal      if a == b
 *             List_comparison::sublist    if a is contained in b
 *             List_comparison::superlist  if b is contained in a
 *             List_comparison::unequal    otherwise
 */
template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b) {
    // Fast path: identical vectors
    if (a == b) {
        return List_comparison::equal;
    }

    // Helper lambda to test whether `small` appears as a contiguous
    // subsequence inside `big`
    auto is_sublist = [](const std::vector<T>& small, const std::vector<T>& big) -> bool {
        if (small.empty()) {
            return true;            // empty list is a sub-list of every list
        }
        return std::search(big.begin(), big.end(), small.begin(), small.end()) != big.end();
    };

    if (is_sublist(a, b)) {
        return List_comparison::sublist;
    }
    if (is_sublist(b, a)) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
