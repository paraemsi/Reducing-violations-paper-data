#pragma once

#include <vector>
#include <algorithm>
#include <iterator>

namespace sublist {

// Possible relationships between two lists.
enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

// Backwards-compatibility type alias (not used by tests but may help users)
using Comparison = List_comparison;

// Return the relationship of list A to list B.
//
// The function works with any element type that is equality‐comparable.
template <typename T>
[[nodiscard]] inline List_comparison sublist(const std::vector<T>& a,
                                             const std::vector<T>& b) {
    if (a == b) return List_comparison::equal;

    auto is_sub = [](const std::vector<T>& small,
                     const std::vector<T>& large) -> bool {
        if (small.empty()) return true;
        if (small.size() > large.size()) return false;

        return std::search(large.begin(), large.end(),
                           small.begin(), small.end()) != large.end();
    };

    if (is_sub(a, b)) return List_comparison::sublist;
    if (is_sub(b, a)) return List_comparison::superlist;

    return List_comparison::unequal;
}

}  // namespace sublist
