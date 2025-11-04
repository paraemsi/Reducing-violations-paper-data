#include "sublist.h"
#include <vector>

namespace sublist {

List_comparison sublist(const std::vector<int>& list1, const std::vector<int>& list2) {
    // Handle the case where both lists are equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a sublist of list2
    // An empty list is always a sublist of any list
    if (list1.size() <= list2.size()) {
        for (std::size_t i = 0; i <= (list2.size() - list1.size()); ++i) {
            bool is_sublist = true;
            for (std::size_t j = 0; j < list1.size(); ++j) {
                if (list2[i + j] != list1[j]) {
                    is_sublist = false;
                    break;
                }
            }
            if (is_sublist) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list2 is a sublist of list1 (making list1 a superlist)
    if (list2.size() <= list1.size()) {
        for (std::size_t i = 0; i <= (list1.size() - list2.size()); ++i) {
            bool is_sublist = true;
            for (std::size_t j = 0; j < list2.size(); ++j) {
                if (list1[i + j] != list2[j]) {
                    is_sublist = false;
                    break;
                }
            }
            if (is_sublist) {
                return List_comparison::superlist;
            }
        }
    }
    
    // If neither is a sublist of the other and they're not equal, they're unequal
    return List_comparison::unequal;
}

}  // namespace sublist
