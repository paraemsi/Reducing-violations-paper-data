#include "sublist.h"
#include <vector>
#include <cstdint>

namespace sublist {

List_comparison sublist(const std::vector<int>& list1, const std::vector<int>& list2) {
    // Check if equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a sublist of list2
    if (list1.size() <= list2.size()) {
        std::uint64_t list1_size = static_cast<std::uint64_t>(list1.size());
        std::uint64_t list2_size = static_cast<std::uint64_t>(list2.size());
        for (std::uint64_t i = 0; i <= (list2_size - list1_size); i++) {
            bool found = true;
            for (std::uint64_t j = 0; j < list1_size; j++) {
                if (list2[static_cast<std::size_t>((i + j))] != list1[static_cast<std::size_t>(j)]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list1 is a superlist of list2 (list2 is a sublist of list1)
    if (list1.size() >= list2.size()) {
        std::uint64_t list1_size = static_cast<std::uint64_t>(list1.size());
        std::uint64_t list2_size = static_cast<std::uint64_t>(list2.size());
        for (std::uint64_t i = 0; i <= (list1_size - list2_size); i++) {
            bool found = true;
            for (std::uint64_t j = 0; j < list2_size; j++) {
                if (list1[static_cast<std::size_t>((i + j))] != list2[static_cast<std::size_t>(j)]) {
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
