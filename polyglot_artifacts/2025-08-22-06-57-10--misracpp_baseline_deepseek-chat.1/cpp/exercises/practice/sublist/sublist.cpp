#include "sublist.h"
#include <vector>
#include <algorithm>

namespace sublist {

List_comparison sublist(const std::vector<int>& list1, const std::vector<int>& list2) {
    // Check if they're equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a sublist of list2
    if (list1.size() < list2.size()) {
        for (size_t i = 0; i <= list2.size() - list1.size(); ++i) {
            if (std::equal(list1.begin(), list1.end(), list2.begin() + i)) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list1 is a superlist of list2 (list2 is a sublist of list1)
    if (list1.size() > list2.size()) {
        for (size_t i = 0; i <= list1.size() - list2.size(); ++i) {
            if (std::equal(list2.begin(), list2.end(), list1.begin() + i)) {
                return List_comparison::superlist;
            }
        }
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
