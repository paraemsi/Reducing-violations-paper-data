#include "sublist.h"
#include <vector>
#include <cstdint>
#include <cstddef>

namespace sublist {

List_comparison sublist(const std::vector<std::int32_t>& list1, const std::vector<std::int32_t>& list2) {
    // Check if lists are equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a sublist of list2
    if ((list1.size()) <= (list2.size())) {
        for (std::size_t i = 0; (i) <= ((list2.size()) - (list1.size())); i++) {
            bool found = true;
            for (std::size_t j = 0; (j) < (list1.size()); j++) {
                if ((list2[(i) + (j)]) != (list1[j])) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list1 is a superlist of list2 (which means list2 is a sublist of list1)
    if ((list1.size()) >= (list2.size())) {
        for (std::size_t i = 0; (i) <= ((list1.size()) - (list2.size())); i++) {
            bool found = true;
            for (std::size_t j = 0; (j) < (list2.size()); j++) {
                if ((list1[(i) + (j)]) != (list2[j])) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::superlist;
            }
        }
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
