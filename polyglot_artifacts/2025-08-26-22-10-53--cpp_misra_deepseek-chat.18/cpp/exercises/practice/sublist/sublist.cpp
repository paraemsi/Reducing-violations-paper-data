#include "sublist.h"
#include <vector>
#include <cstddef>

namespace sublist {

List_comparison sublist(const std::vector<int>& list1, const std::vector<int>& list2) {
    // Check if lists are equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a superlist of list2 (meaning list2 is a sublist of list1)
    if (list1.size() > list2.size()) {
        for (std::size_t i = 0; i <= (list1.size() - list2.size()); ++i) {
            bool found = true;
            for (std::size_t j = 0; j < list2.size(); ++j) {
                if (list1[i + j] != list2[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::superlist;
            }
        }
    }
    
    // Check if list1 is a sublist of list2 (meaning list2 is a superlist of list1)
    if (list1.size() < list2.size()) {
        for (std::size_t i = 0; i <= (list2.size() - list1.size()); ++i) {
            bool found = true;
            for (std::size_t j = 0; j < list1.size(); ++j) {
                if (list2[i + j] != list1[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::sublist;
            }
        }
    }
    
    // If none of the above conditions are met, the lists are unequal
    return List_comparison::unequal;
}

}  // namespace sublist
