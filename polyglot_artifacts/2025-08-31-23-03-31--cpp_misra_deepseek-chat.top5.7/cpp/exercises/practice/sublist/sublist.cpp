#include "sublist.h"
#include <vector>
#include <cstdint>

namespace sublist {

template <typename T>
bool is_sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    if (list_a.empty()) {
        return true;
    }
    
    const std::uint64_t a_size = static_cast<std::uint64_t>(list_a.size());
    const std::uint64_t b_size = static_cast<std::uint64_t>(list_b.size());
    
    // Ensure list_a is not larger than list_b to prevent underflow
    if (a_size > b_size) {
        return false;
    }
    
    for (std::uint64_t i = 0; i <= (b_size - a_size); ++i) {
        bool found = true;
        for (std::uint64_t j = 0; j < a_size; ++j) {
            if (list_b[static_cast<typename std::vector<T>::size_type>(i + j)] != list_a[static_cast<typename std::vector<T>::size_type>(j)]) {
                found = false;
                break;
            }
        }
        if (found) {
            return true;
        }
    }
    return false;
}

template <typename T>
List_comparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    const std::uint64_t a_size = static_cast<std::uint64_t>(list_a.size());
    const std::uint64_t b_size = static_cast<std::uint64_t>(list_b.size());
    
    if (a_size == b_size) {
        bool are_equal = true;
        for (std::uint64_t i = 0; i < a_size; ++i) {
            if (list_a[static_cast<typename std::vector<T>::size_type>(i)] != list_b[static_cast<typename std::vector<T>::size_type>(i)]) {
                are_equal = false;
                break;
            }
        }
        if (are_equal) {
            return List_comparison::equal;
        }
    }
    
    if (a_size < b_size) {
        if (is_sublist(list_a, list_b)) {
            return List_comparison::sublist;
        }
    } else {
        if (is_sublist(list_b, list_a)) {
            return List_comparison::superlist;
        }
    }
    
    return List_comparison::unequal;
}

// Explicit template instantiations
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);
}  // namespace sublist
