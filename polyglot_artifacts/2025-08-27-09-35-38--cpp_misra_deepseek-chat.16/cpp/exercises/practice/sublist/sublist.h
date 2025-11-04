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
    // Check if equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Handle cases where one of the lists is empty
    // An empty list is always a sublist of any list
    if (list1.empty()) {
        return List_comparison::sublist;
    }
    if (list2.empty()) {
        return List_comparison::superlist;
    }
    
    // Define a type for indices - use a large enough fixed-width type
    using size_type = std::uint64_t;
    
    // Check if list1 is a superlist of list2 (list2 is a sublist of list1)
    // Which means list1 contains list2 as a contiguous subsequence
    const size_type size1 = static_cast<size_type>(list1.size());
    const size_type size2 = static_cast<size_type>(list2.size());
    
    // Check if list1 is a superlist of list2
    if (size1 > size2) {
        // The maximum starting index in list1 where list2 could fit
        const size_type max_i = (size1 - size2);
        for (size_type i = 0; i <= max_i; ++i) {
            bool found = true;
            for (size_type j = 0; j < size2; ++j) {
                // Add parentheses to ensure proper precedence
                const size_type index1 = static_cast<typename std::vector<T>::size_type>((i + j));
                const size_type index2 = static_cast<typename std::vector<T>::size_type>(j);
                if ((list1[index1] != list2[index2])) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::superlist;
            }
        }
    }
    
    // Check if list1 is a sublist of list2 (list2 is a superlist of list1)
    if (size1 < size2) {
        // The maximum starting index in list2 where list1 could fit
        const size_type max_i = (size2 - size1);
        for (size_type i = 0; i <= max_i; ++i) {
            bool found = true;
            for (size_type j = 0; j < size1; ++j) {
                // Add parentheses to ensure proper precedence
                const size_type index1 = static_cast<typename std::vector<T>::size_type>((i + j));
                const size_type index2 = static_cast<typename std::vector<T>::size_type>(j);
                if ((list2[index1] != list1[index2])) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::sublist;
            }
        }
    }
    
    // If none of the above
    return List_comparison::unequal;
}

}  // namespace sublist
