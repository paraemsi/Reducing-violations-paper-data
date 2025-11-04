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
    // Handle empty lists first
    if (list1.empty() && list2.empty()) {
        return List_comparison::equal;
    } else if (list1.empty()) {
        // An empty list is a sublist of any non-empty list
        return List_comparison::sublist;
    } else if (list2.empty()) {
        // Any non-empty list is a superlist of an empty list
        return List_comparison::superlist;
    }
    
    // Check if list1 is equal to list2
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a superlist of list2 (list1 contains list2)
    if (list1.size() > list2.size()) {
        std::int64_t max_start = (static_cast<std::int64_t>(list1.size()) - static_cast<std::int64_t>(list2.size()));
        for (std::int64_t i = 0; i <= max_start; i++) {
            bool found = true;
            for (std::int64_t j = 0; j < static_cast<std::int64_t>(list2.size()); j++) {
                if ((list1[static_cast<std::size_t>((i + j))] != list2[static_cast<std::size_t>(j)])) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::superlist;
            }
        }
    }
    
    // Check if list1 is a sublist of list2 (list2 contains list1)
    if (list1.size() < list2.size()) {
        std::int64_t max_start = (static_cast<std::int64_t>(list2.size()) - static_cast<std::int64_t>(list1.size()));
        for (std::int64_t i = 0; i <= max_start; i++) {
            bool found = true;
            for (std::int64_t j = 0; j < static_cast<std::int64_t>(list1.size()); j++) {
                if ((list2[static_cast<std::size_t>((i + j))] != list1[static_cast<std::size_t>(j)])) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::sublist;
            }
        }
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
