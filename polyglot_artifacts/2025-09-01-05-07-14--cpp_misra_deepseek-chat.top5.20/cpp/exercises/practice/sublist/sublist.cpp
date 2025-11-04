#include "sublist.h"
#include <vector>
#include <cstdint>

namespace sublist {

List_comparison sublist(const std::vector<int>& list1, const std::vector<int>& list2) {
    // Handle empty cases first
    if (list1.empty()) {
        if (list2.empty()) {
            return List_comparison::equal;
        } else {
            return List_comparison::sublist;
        }
    } else {
        if (list2.empty()) {
            return List_comparison::superlist;
        }
    }
    
    // Check if equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a sublist of list2 (list2 contains list1)
    std::int32_t list1_size = static_cast<std::int32_t>(list1.size());
    std::int32_t list2_size = static_cast<std::int32_t>(list2.size());
    
    // Check if list1 is a sublist of list2
    if (list1_size <= list2_size) {
        for (std::int32_t i = 0; i <= (list2_size - list1_size); ++i) {
            bool match = true;
            for (std::int32_t j = 0; j < list1_size; ++j) {
                if (list2[static_cast<size_t>(i) + static_cast<size_t>(j)] != list1[static_cast<size_t>(j)]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list1 is a superlist of list2 (list1 contains list2)
    if (list1_size >= list2_size) {
        for (std::int32_t i = 0; i <= (list1_size - list2_size); ++i) {
            bool match = true;
            for (std::int32_t j = 0; j < list2_size; ++j) {
                if (list1[static_cast<size_t>(i) + static_cast<size_t>(j)] != list2[static_cast<size_t>(j)]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return List_comparison::superlist;
            }
        }
    }
    
    // If none of the above, they're unequal
    return List_comparison::unequal;
}

}  // namespace sublist
