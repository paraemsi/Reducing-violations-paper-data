#include "sublist.h"
#include <vector>
#include <cstdint>

namespace sublist {

List_comparison sublist(const std::vector<int>& list_a, const std::vector<int>& list_b) {
    // Check if equal
    if (list_a == list_b) {
        return List_comparison::equal;
    }
    
    // Check if list_a is a sublist of list_b
    if (list_a.size() <= list_b.size()) {
        for (std::size_t i = 0; i <= (list_b.size() - list_a.size()); i++) {
            bool match = true;
            for (std::size_t j = 0; j < list_a.size(); j++) {
                if (list_b[i + j] != list_a[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list_b is a sublist of list_a (making list_a a superlist)
    if (list_b.size() <= list_a.size()) {
        for (std::size_t i = 0; i <= (list_a.size() - list_b.size()); i++) {
            bool match = true;
            for (std::size_t j = 0; j < list_b.size(); j++) {
                if (list_a[i + j] != list_b[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return List_comparison::superlist;
            }
        }
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
