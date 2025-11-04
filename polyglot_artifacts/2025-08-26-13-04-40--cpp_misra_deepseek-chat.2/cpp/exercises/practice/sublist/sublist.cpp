#include "sublist.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace sublist {

template <typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Check if the lists are equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Handle cases where one of the lists is empty
    if (list1.empty()) {
        // An empty list is always a sublist of any list
        return List_comparison::sublist;
    }
    if (list2.empty()) {
        // If list2 is empty and list1 is not, list1 is a superlist
        return List_comparison::superlist;
    }
    
    // Check if list1 is a superlist of list2 (list1 contains list2)
    if (list1.size() > list2.size()) {
        // Check if list2 is a contiguous subsequence of list1
        for (typename std::vector<T>::size_type i = 0; i <= (list1.size() - list2.size()); ++i) {
            if (std::equal(list2.begin(), list2.end(), list1.begin() + i)) {
                return List_comparison::superlist;
            }
        }
    }
    
    // Check if list1 is a sublist of list2 (list2 contains list1)
    if (list1.size() < list2.size()) {
        for (typename std::vector<T>::size_type i = 0; i <= (list2.size() - list1.size()); ++i) {
            if (std::equal(list1.begin(), list1.end(), list2.begin() + i)) {
                return List_comparison::sublist;
            }
        }
    }
    
    // If none of the above, the lists are unequal
    return List_comparison::unequal;
}

// Explicit instantiation for int
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);
}  // namespace sublist
