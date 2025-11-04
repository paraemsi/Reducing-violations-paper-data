#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<int>& list_a, const std::vector<int>& list_b) {
    // Check if list_a is equal to list_b
    if (list_a == list_b) {
        return List_comparison::equal;
    }
    
    // Check if list_a is a superlist of list_b (list_b is a sublist of list_a)
    // This means list_b is contained within list_a
    if (list_a.size() > list_b.size()) {
        const std::uint64_t a_size = static_cast<std::uint64_t>(list_a.size());
        const std::uint64_t b_size = static_cast<std::uint64_t>(list_b.size());
        for (std::uint64_t i = 0; i <= (a_size - b_size); ++i) {
            bool found = true;
            for (std::uint64_t j = 0; j < b_size; ++j) {
                if ((list_a[static_cast<std::vector<int>::size_type>(i + j)] != list_b[static_cast<std::vector<int>::size_type>(j)])) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::superlist;
            }
        }
    }
    
    // Check if list_a is a sublist of list_b (list_a is contained within list_b)
    if (list_a.size() < list_b.size()) {
        const std::uint64_t a_size = static_cast<std::uint64_t>(list_a.size());
        const std::uint64_t b_size = static_cast<std::vector<int>::size_type>(list_b.size());
        for (std::uint64_t i = 0; i <= (b_size - a_size); ++i) {
            bool found = true;
            for (std::uint64_t j = 0; j < a_size; ++j) {
                if ((list_b[static_cast<std::vector<int>::size_type>(i + j)] != list_a[static_cast<std::vector<int>::size_type>(j)])) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::sublist;
            }
        }
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
