#include "sublist.h"
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cstddef>

namespace sublist {

List_comparison sublist(const std::vector<std::int32_t>& list1, 
                       const std::vector<std::int32_t>& list2) {
    // Check if lists are equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Helper lambda to check if list1 is a sublist of list2
    auto is_sublist = [](const std::vector<std::int32_t>& sub, 
                         const std::vector<std::int32_t>& super) -> bool {
        if (sub.empty()) {
            return true;
        }
        if (super.size() < sub.size()) {
            return false;
        }
        for (std::uint64_t i = 0; i <= (static_cast<std::uint64_t>(super.size()) - static_cast<std::uint64_t>(sub.size())); ++i) {
            bool found = true;
            for (std::uint64_t j = 0; j < static_cast<std::uint64_t>(sub.size()); ++j) {
                if (super[i + j] != sub[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return true;
            }
        }
        return false;
    };
    
    // Check if list1 is a sublist of list2
    if (is_sublist(list1, list2)) {
        return List_comparison::sublist;
    }
    
    // Check if list2 is a sublist of list1 (making list1 a superlist)
    if (is_sublist(list2, list1)) {
        return List_comparison::superlist;
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
