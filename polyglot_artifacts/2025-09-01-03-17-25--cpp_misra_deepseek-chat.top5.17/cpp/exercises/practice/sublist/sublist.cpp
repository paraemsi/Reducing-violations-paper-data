#include "sublist.h"
#include <vector>
#include <cstdint>
#include <cstddef>

namespace sublist {

template <typename T>
bool is_sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    if (list_a.empty()) {
        return true;
    }
    
    const std::size_t a_size = list_a.size();
    const std::size_t b_size = list_b.size();
    
    for (std::size_t i = 0; i <= (b_size - a_size); ++i) {
        bool match = true;
        for (std::size_t j = 0; j < a_size; ++j) {
            if (list_b[i + j] != list_a[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

template <typename T>
List_comparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    if (list_a.size() == list_b.size()) {
        // Check if they're equal
        bool are_equal = true;
        for (std::size_t i = 0; i < list_a.size(); ++i) {
            if (list_a[i] != list_b[i]) {
                are_equal = false;
                break;
            }
        }
        if (are_equal) {
            return List_comparison::equal;
        }
    }
    
    // Check if list_a is a sublist of list_b
    if (list_a.size() < list_b.size()) {
        if (is_sublist(list_a, list_b)) {
            return List_comparison::sublist;
        }
    } else {
        if (list_a.size() > list_b.size()) {
            // Check if list_b is a sublist of list_a, which makes list_a a superlist
            if (is_sublist(list_b, list_a)) {
                return List_comparison::superlist;
            }
        }
    }
    
    // If none of the above conditions are true
    return List_comparison::unequal;
}

// Explicit template instantiations
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);
// Add other types as needed

}  // namespace sublist
