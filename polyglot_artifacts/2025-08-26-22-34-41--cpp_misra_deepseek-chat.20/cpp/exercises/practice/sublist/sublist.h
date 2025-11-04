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
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Check if list1 is equal to list2
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a sublist of list2
    // list1 is empty, which is always a sublist
    if (list1.empty()) {
        return List_comparison::sublist;
    }
    // Check if list2 is empty, which would make list1 not a sublist (since list1 is not empty)
    if (list2.empty()) {
        return List_comparison::superlist;
    }
    
    // Check if list1 is a sublist of list2 (only if list2 is at least as long as list1)
    if (list2.size() >= list1.size()) {
        // To avoid potential underflow, we can compute the maximum index
        const std::size_t max_index = (list2.size() - list1.size());
        for (std::size_t i = 0; (i <= max_index); i++) {
            bool found = true;
            for (std::size_t j = 0; (j < list1.size()); j++) {
                if ((list2[(i + j)] != list1[j])) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list2 is a sublist of list1 (making list1 a superlist) (only if list1 is at least as long as list2)
    if (list1.size() >= list2.size()) {
        const std::size_t max_index = (list1.size() - list2.size());
        for (std::size_t i = 0; (i <= max_index); i++) {
            bool found = true;
            for (std::size_t j = 0; (j < list2.size()); j++) {
                if ((list1[(i + j)] != list2[j])) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::superlist;
            }
        }
    }
    
    // None of the above
    return List_comparison::unequal;
}

}  // namespace sublist
