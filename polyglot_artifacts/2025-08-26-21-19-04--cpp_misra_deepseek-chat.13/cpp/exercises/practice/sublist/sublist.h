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
    // Handle empty lists
    if (list1.empty() && list2.empty()) {
        return List_comparison::equal;
    }
    if (list1.empty()) {
        return List_comparison::sublist;
    }
    if (list2.empty()) {
        return List_comparison::superlist;
    }
    
    // Check if lists are equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a superlist of list2 (list2 is a sublist of list1)
    if (list1.size() > list2.size()) {
        std::uint64_t list1_size = static_cast<std::uint64_t>(list1.size());
        std::uint64_t list2_size = static_cast<std::uint64_t>(list2.size());
        std::uint64_t max_i = (list1_size - list2_size);
        for (std::uint64_t i = 0; i <= max_i; i++) {
            bool found = true;
            for (std::uint64_t j = 0; j < list2_size; j++) {
                if (list1[(i + j)] != list2[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::superlist;
            }
        }
    }
    
    // Check if list1 is a sublist of list2
    if (list1.size() < list2.size()) {
        std::uint64_t list1_size = static_cast<std::uint64_t>(list1.size());
        std::uint64_t list2_size = static_cast<std::uint64_t>(list2.size());
        std::uint64_t max_i = (list2_size - list1_size);
        for (std::uint64_t i = 0; i <= max_i; i++) {
            bool found = true;
            for (std::uint64_t j = 0; j < list1_size; j++) {
                if (list2[(i + j)] != list1[j]) {
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
