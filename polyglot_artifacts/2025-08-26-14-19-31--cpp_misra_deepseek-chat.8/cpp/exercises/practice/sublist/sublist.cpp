#include "sublist.h"
#include <vector>
#include <cstddef>

namespace sublist {

template <typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Check if lists are equal
    if (list1.size() == list2.size()) {
        bool are_equal = true;
        for (size_t i = 0; i < list1.size(); ++i) {
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
    // An empty list is always a sublist of any list
    if (list1.size() == 0) {
        return List_comparison::sublist;
    }
    
    // Check if list1 is a sublist of list2
    // An empty list is always a sublist of any list
    if (list1.size() == 0) {
        return List_comparison::sublist;
    }
    
    // Check if list1 is contained within list2
    if (list1.size() <= list2.size()) {
        // To prevent underflow, we can compute the maximum index to start at
        // Since list1.size() <= list2.size(), list2.size() - list1.size() is >= 0
        for (size_t i = 0; i <= list2.size() - list1.size(); ++i) {
            bool match = true;
            for (size_t j = 0; j < list1.size(); ++j) {
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
    
    // Check if list2 is a sublist of list1 (making list1 a superlist)
    // An empty list2 would make list1 a superlist
    if (list2.size() == 0) {
        return List_comparison::superlist;
    }
    
    if (list2.size() <= list1.size()) {
        // Similarly, list2.size() <= list1.size(), so no underflow
        for (size_t i = 0; i <= list1.size() - list2.size(); ++i) {
            bool match = true;
            for (size_t j = 0; j < list2.size(); ++j) {
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

// Explicit template instantiation for int
template List_comparison sublist(const std::vector<int>&, const std::vector<int>&);

}  // namespace sublist
