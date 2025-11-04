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
bool is_sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    const std::size_t size1 = list1.size();
    const std::size_t size2 = list2.size();
    
    if (size1 > size2) {
        return false;
    }
    if (size1 == 0U) {
        return true;
    }
    
    for (std::size_t i = 0U; i <= (size2 - size1); ++i) {
        bool match = true;
        for (std::size_t j = 0U; j < size1; ++j) {
            if (!(list2[(i + j)] == list1[j])) {
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
    const std::size_t size1 = list1.size();
    const std::size_t size2 = list2.size();
    
    if (size1 == size2) {
        // Check if they're equal
        bool are_equal = true;
        for (std::size_t i = 0U; i < size1; ++i) {
            if (!(list1[i] == list2[i])) {
                are_equal = false;
                break;
            }
        }
        if (are_equal) {
            return List_comparison::equal;
        }
    }
    
    if (is_sublist(list1, list2)) {
        return List_comparison::sublist;
    }
    if (is_sublist(list2, list1)) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
