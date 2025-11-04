#include "sublist.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace sublist {

template <typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Check if equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is empty, then it's a sublist of list2
    if (list1.empty()) {
        return List_comparison::sublist;
    }
    
    // Check if list2 is empty, then list1 is a superlist of list2
    if (list2.empty()) {
        return List_comparison::superlist;
    }
    
    // Check if list1 is a sublist of list2
    if (list1.size() <= list2.size()) {
        for (std::size_t i = 0; i <= (list2.size() - list1.size()); ++i) {
            if (std::equal(list1.begin(), list1.end(), list2.begin() + i)) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list1 is a superlist of list2 (i.e., list2 is a sublist of list1)
    if (list2.size() <= list1.size()) {
        for (std::size_t i = 0; i <= (list1.size() - list2.size()); ++i) {
            if (std::equal(list2.begin(), list2.end(), list1.begin() + i)) {
                return List_comparison::superlist;
            }
        }
    }
    
    // None of the above
    return List_comparison::unequal;
}

// Explicit instantiation for int
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);

}  // namespace sublist
