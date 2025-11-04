#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <vector>

namespace sublist {

// The relationship between two lists.
enum class List_comparison { equal, sublist, superlist, unequal };
using comparison_result = List_comparison;

// Helper: check if 'haystack' contains 'needle' as a contiguous subsequence.
template <typename T>
inline bool contains(const std::vector<T>& haystack, const std::vector<T>& needle) {
    if (needle.empty()) {
        return true;  // Empty list is a sublist of any list
    }
    if (needle.size() > haystack.size()) {
        return false;
    }
    auto it = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end());
    return it != haystack.end();
}

// Compare two lists A and B and classify their relationship.
// - equal:     A and B have identical elements in the same order
// - sublist:   A appears as a contiguous subsequence within B
// - superlist: B appears as a contiguous subsequence within A
// - unequal:   none of the above
template <typename T>
inline List_comparison compare(const std::vector<T>& a, const std::vector<T>& b) {
    if (a == b) {
        return List_comparison::equal;
    }

    // uses helper contains<T> defined above

    if (contains(a, b)) {
        return List_comparison::superlist;
    }
    if (contains(b, a)) {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b) {
    return compare(a, b);
}

inline List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) {
    const std::vector<int> va(a);
    const std::vector<int> vb(b);
    return sublist(va, vb);
}

template <typename T>
inline List_comparison sublist(std::initializer_list<T> a, std::initializer_list<T> b) {
    const std::vector<T> va(a);
    const std::vector<T> vb(b);
    return sublist(va, vb);
}

}  // namespace sublist
