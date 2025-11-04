#include "sublist.h"
#include <vector>
#include <cstdint>

namespace sublist {

template <typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Check if equal first
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a superlist of list2
    if (list1.size() > list2.size()) {
        for (std::int64_t i = 0; i <= (static_cast<std::int64_t>(list1.size()) - static_cast<std::int64_t>(list2.size())); ++i) {
            bool match = true;
            for (std::int64_t j = 0; j < static_cast<std::int64_t>(list2.size()); ++j) {
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
    
    // Check if list1 is a sublist of list2
    if (list1.size() < list2.size()) {
        for (std::int64_t i = 0; i <= (static_cast<std::int64_t>(list2.size()) - static_cast<std::int64_t>(list1.size())); ++i) {
            bool match = true;
            for (std::int64_t j = 0; j < static_cast<std::int64_t>(list1.size()); ++j) {
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
    
    // Handle cases where one or both are empty
    if (list1.empty() && !list2.empty()) {
        return List_comparison::sublist;
    }
    if (!list1.empty() && list2.empty()) {
        return List_comparison::superlist;
    }
    
    return List_comparison::unequal;
}

// Explicit template instantiation
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);

}  // namespace sublist
