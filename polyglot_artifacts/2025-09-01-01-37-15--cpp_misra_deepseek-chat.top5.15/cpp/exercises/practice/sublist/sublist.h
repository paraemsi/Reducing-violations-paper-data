#pragma once
#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison {
    equal,
    unequal,
    sublist,
    superlist
};

template <typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Check if list1 is equal to list2
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Handle cases where either list is empty
    if (list1.empty()) {
        // Empty list is always a sublist of any list
        return List_comparison::sublist;
    } 
    if (list2.empty()) {
        // Non-empty list1 can't be a sublist of empty list2, but it's a superlist
        return List_comparison::superlist;
    }
    
    // Check if list1 is a sublist of list2
    if ((list1.size() <= list2.size())) {
        const std::size_t diff = (list2.size() - list1.size());
        for (std::size_t i = 0; i <= diff; i++) {
            bool match = true;
            for (std::size_t j = 0; j < list1.size(); j++) {
                if (!((list2[(i + j)]) == (list1[j]))) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list1 is a superlist of list2 (list2 is a sublist of list1)
    if ((list1.size() >= list2.size())) {
        const std::size_t diff = (list1.size() - list2.size());
        for (std::size_t i = 0; i <= diff; i++) {
            bool match = true;
            for (std::size_t j = 0; j < list2.size(); j++) {
                if (!((list1[(i + j)]) == (list2[j]))) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return List_comparison::superlist;
            }
        }
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
