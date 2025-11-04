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
    // Check if lists are equal first
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Handle cases where one list is empty
    // If list1 is empty, it's a sublist of list2 (unless list2 is also empty, which was handled above)
    if (list1.empty()) {
        return List_comparison::sublist;
    }
    // If list2 is empty, list1 is a superlist of list2 (since list2 is empty and list1 is not empty)
    if (list2.empty()) {
        return List_comparison::superlist;
    }
    
    // Check if list1 is a sublist of list2
    if (list1.size() <= list2.size()) {
        const std::uint64_t size_diff = static_cast<std::uint64_t>(list2.size()) - static_cast<std::uint64_t>(list1.size());
        for (std::uint64_t i = 0; i <= size_diff; ++i) {
            bool match = true;
            for (std::uint64_t j = 0; j < static_cast<std::uint64_t>(list1.size()); ++j) {
                if (list2[i + j] != list1[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list1 is a superlist of list2 (i.e., list2 is a sublist of list1)
    if (list1.size() >= list2.size()) {
        const std::uint64_t size_diff = static_cast<std::uint64_t>(list1.size()) - static_cast<std::uint64_t>(list2.size());
        for (std::uint64_t i = 0; i <= size_diff; ++i) {
            bool match = true;
            for (std::uint64_t j = 0; j < static_cast<std::uint64_t>(list2.size()); ++j) {
                if (list1[i + j] != list2[j]) {
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
