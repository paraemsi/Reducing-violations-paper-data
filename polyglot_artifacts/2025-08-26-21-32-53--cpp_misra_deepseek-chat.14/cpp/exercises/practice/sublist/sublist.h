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
bool is_sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    if (list1.empty()) {
        return true;
    }
    const std::uint64_t list1_size = static_cast<std::uint64_t>(list1.size());
    const std::uint64_t list2_size = static_cast<std::uint64_t>(list2.size());
    
    // Check if list2 can possibly contain list1
    if (list2_size < list1_size) {
        return false;
    }
    
    // To avoid potential issues with large sizes, we need to make sure the subtraction doesn't underflow
    // Since list2_size >= list1_size, (list2_size - list1_size) is safe
    for (std::uint64_t i = 0; i <= (list2_size - list1_size); ++i) {
        bool match = true;
        for (std::uint64_t j = 0; j < list1_size; ++j) {
            // Use at() to be safe? Or direct indexing with proper cast
            // Since i + j and j are within bounds, it's safe
            if (list2[static_cast<typename std::vector<T>::size_type>(i + j)] != 
                list1[static_cast<typename std::vector<T>::size_type>(j)]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

template <typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Handle cases where either list is empty
    if (list1.empty() && list2.empty()) {
        return List_comparison::equal;
    } else if (list1.empty()) {
        return List_comparison::sublist;
    } else if (list2.empty()) {
        return List_comparison::superlist;
    }
    
    const std::uint64_t size1 = static_cast<std::uint64_t>(list1.size());
    const std::uint64_t size2 = static_cast<std::uint64_t>(list2.size());
    
    // Check for equality
    if (size1 == size2) {
        bool are_equal = true;
        for (typename std::vector<T>::size_type i = 0; i < list1.size(); ++i) {
            if (list1[i] != list2[i]) {
                are_equal = false;
                break;
            }
        }
        if (are_equal) {
            return List_comparison::equal;
        }
    }
    
    // Check if list1 is a sublist of list2
    if (size1 < size2) {
        if (is_sublist(list1, list2)) {
            return List_comparison::sublist;
        }
    }
    
    // Check if list1 is a superlist of list2 (i.e., list2 is a sublist of list1)
    if (size1 > size2) {
        if (is_sublist(list2, list1)) {
            return List_comparison::superlist;
        }
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
