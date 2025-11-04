#pragma once
#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
bool is_sublist(const std::vector<T>& list, const std::vector<T>& sublist) {
    // An empty list is always a sublist
    if (sublist.empty()) {
        return true;
    }
    // If the list is smaller than the sublist, it can't contain it
    if (list.size() < sublist.size()) {
        return false;
    }
    
    // Check each possible starting position
    for (typename std::vector<T>::size_type i = 0; i <= (list.size() - sublist.size()); ++i) {
        bool found = true;
        for (typename std::vector<T>::size_type j = 0; j < sublist.size(); ++j) {
            if ((list[(i + j)]) != (sublist[j])) {
                found = false;
                break;
            }
        }
        if (found) {
            return true;
        }
    }
    return false;
}

template <typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    if ((list1.size()) == (list2.size())) {
        // Check if they're equal
        bool are_equal = true;
        for (typename std::vector<T>::size_type i = 0; i < list1.size(); ++i) {
            if ((list1[i]) != (list2[i])) {
                are_equal = false;
                break;
            }
        }
        if (are_equal) {
            return List_comparison::equal;
        }
    }
    
    // Check if list1 is a superlist of list2 (list2 is a sublist of list1)
    if (is_sublist(list1, list2)) {
        return List_comparison::superlist;
    }
    // Check if list1 is a sublist of list2
    if (is_sublist(list2, list1)) {
        return List_comparison::sublist;
    }
    // Otherwise, they're unequal
    return List_comparison::unequal;
}

}  // namespace sublist
