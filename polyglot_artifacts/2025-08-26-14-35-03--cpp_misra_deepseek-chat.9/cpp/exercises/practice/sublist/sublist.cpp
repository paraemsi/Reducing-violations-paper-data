#include "sublist.h"
#include <vector>
#include <cstdint>

namespace sublist {

// Helper function to check if list2 is a sublist of list1
template <typename T>
bool is_sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Handle cases where list2 is empty (always a sublist)
    if (list2.empty()) {
        return true;
    }
    // If list1 is smaller than list2, list2 can't be a sublist
    if (list1.size() < list2.size()) {
        return false;
    }
    
    // Check each possible starting position in list1
    for (std::size_t i = 0; i <= (list1.size() - list2.size()); ++i) {
        bool match = true;
        for (std::size_t j = 0; j < list2.size(); ++j) {
            if (list1[i + j] != list2[j]) {
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
    // Check if lists are equal first
    if (list1.size() == list2.size()) {
        bool are_equal = true;
        for (std::size_t i = 0; i < list1.size(); ++i) {
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
    if (is_sublist(list1, list2)) {
        return List_comparison::superlist;
    }
    // Check if list1 is a sublist of list2 (list2 contains list1)
    if (is_sublist(list2, list1)) {
        return List_comparison::sublist;
    }
    // None of the above
    return List_comparison::unequal;
}

// Explicit instantiation for int
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);

}  // namespace sublist
