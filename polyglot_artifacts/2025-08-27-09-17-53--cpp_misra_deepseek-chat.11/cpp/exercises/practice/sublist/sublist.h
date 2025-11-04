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
    // Check if the lists are equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a superlist of list2 (list1 contains list2)
    if (list1.size() > list2.size()) {
        // Handle cases where list2 is empty
        if (list2.size() == 0) {
            return List_comparison::superlist;
        }
        const std::uint64_t size_diff = static_cast<std::uint64_t>(list1.size()) - static_cast<std::uint64_t>(list2.size());
        for (std::uint64_t i = 0; i <= size_diff; ++i) {
            bool match = true;
            for (std::uint64_t j = 0; j < static_cast<std::uint64_t>(list2.size()); ++j) {
                if ((list1[static_cast<typename std::vector<T>::size_type>(i + j)]) != (list2[static_cast<typename std::vector<T>::size_type>(j)])) {
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
        // Handle cases where list1 is empty
        if (list1.size() == 0) {
            return List_comparison::sublist;
        }
        const std::uint64_t size_diff = static_cast<std::uint64_t>(list2.size()) - static_cast<std::uint64_t>(list1.size());
        for (std::uint64_t i = 0; i <= size_diff; ++i) {
            bool match = true;
            for (std::uint64_t j = 0; j < static_cast<std::uint64_t>(list1.size()); ++j) {
                if ((list2[static_cast<typename std::vector<T>::size_type>(i + j)]) != (list1[static_cast<typename std::vector<T>::size_type>(j)])) {
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
