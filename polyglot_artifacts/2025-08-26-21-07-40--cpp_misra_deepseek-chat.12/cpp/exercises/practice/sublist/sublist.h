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
    // Handle cases with empty lists first
    if (list1.empty() && list2.empty()) {
        return List_comparison::equal;
    } else if (list1.empty()) {
        // An empty list is a sublist of any non-empty list
        return List_comparison::sublist;
    } else if (list2.empty()) {
        // Any non-empty list is a superlist of an empty list
        return List_comparison::superlist;
    }

    // Check for equality
    if (list1.size() == list2.size()) {
        bool are_equal = true;
        for (std::uint64_t i = 0; i < static_cast<std::uint64_t>(list1.size()); ++i) {
            if (list1[i] != list2[i]) {
                are_equal = false;
                break;
            }
        }
        if (are_equal) {
            return List_comparison::equal;
        }
    }
    
    // Check if list1 is a superlist of list2 (list1 contains list2)
    if (list1.size() > list2.size()) {
        // Ensure we don't have underflow by checking sizes first
        const std::uint64_t max_start_index = static_cast<std::uint64_t>(list1.size() - list2.size());
        for (std::uint64_t i = 0; i <= max_start_index; ++i) {
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
    
    // Check if list1 is a sublist of list2 (list2 contains list1)
    if (list1.size() < list2.size()) {
        // Ensure we don't have underflow by checking sizes first
        const std::uint64_t max_start_index = static_cast<std::uint64_t>(list2.size() - list1.size());
        for (std::uint64_t i = 0; i <= max_start_index; ++i) {
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
    
    return List_comparison::unequal;
}

}  // namespace sublist
