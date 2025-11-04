#pragma once

#include <algorithm>
#include <vector>

namespace sublist {

// Possible relationships between two lists.
enum class List_comparison { equal, sublist, superlist, unequal };

// Classify the relationship between list1 and list2.
//
// The function works for any value‐type that supports equality comparison.
template <typename T>
inline List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Equal lists
    if (list1 == list2) {
        return List_comparison::equal;
    }

    // Potential sublist
    if (list1.size() < list2.size()) {
        if (list1.empty() ||
            std::search(list2.begin(), list2.end(),
                         list1.begin(), list1.end()) != list2.end()) {
            return List_comparison::sublist;
        }
    }
    // Potential superlist
    else if (list1.size() > list2.size()) {
        if (list2.empty() ||
            std::search(list1.begin(), list1.end(),
                         list2.begin(), list2.end()) != list1.end()) {
            return List_comparison::superlist;
        }
    }

    // None of the above – unequal
    return List_comparison::unequal;
}

//
// Backwards-compatibility: keep the previous classify() name.
template <typename T>
inline List_comparison classify(const std::vector<T>& list1, const std::vector<T>& list2) {
    return sublist(list1, list2);
}

}  // namespace sublist
