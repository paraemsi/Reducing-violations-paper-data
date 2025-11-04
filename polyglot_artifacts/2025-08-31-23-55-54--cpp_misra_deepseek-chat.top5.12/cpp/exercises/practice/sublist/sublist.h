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
    // Check if list1 is a sublist of list2
    bool is_sublist = false;
    if (list1.size() <= list2.size()) {
        // Handle empty list case
        if (list1.size() == 0U) {
            is_sublist = true;
        } else {
            // Ensure we don't have underflow by checking sizes
            const std::size_t max_index = list2.size() - list1.size();
            for (std::size_t i = 0U; i <= max_index; i++) {
                bool match = true;
                for (std::size_t j = 0U; j < list1.size(); j++) {
                    if (list2[i + j] != list1[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    is_sublist = true;
                    break;
                }
            }
        }
    }
    
    // Check if list2 is a sublist of list1
    bool is_superlist = false;
    if (list2.size() <= list1.size()) {
        // Handle empty list case
        if (list2.size() == 0U) {
            is_superlist = true;
        } else {
            // Ensure we don't have underflow by checking sizes
            const std::size_t max_index = list1.size() - list2.size();
            for (std::size_t i = 0U; i <= max_index; i++) {
                bool match = true;
                for (std::size_t j = 0U; j < list2.size(); j++) {
                    if (list1[i + j] != list2[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    is_superlist = true;
                    break;
                }
            }
        }
    }
    
    // Determine the relationship
    if ((is_sublist) && (is_superlist)) {
        return List_comparison::equal;
    } else if (is_sublist) {
        return List_comparison::sublist;
    } else if (is_superlist) {
        return List_comparison::superlist;
    } else {
        return List_comparison::unequal;
    }
}

}  // namespace sublist
