#pragma once
#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

using size_type = std::uint64_t;

template <typename T>
bool is_sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    const size_type a_size = static_cast<size_type>(list_a.size());
    const size_type b_size = static_cast<size_type>(list_b.size());
    
    // Handle cases where list_a is empty (always a sublist)
    if (a_size == 0) {
        return true;
    }
    // If list_a is longer than list_b, it can't be a sublist
    if (a_size > b_size) {
        return false;
    }
    
    // Check all possible starting positions in list_b
    for (size_type i = 0; i <= (b_size - a_size); ++i) {
        bool match = true;
        for (size_type j = 0; j < a_size; ++j) {
            // Since i + j and j are within bounds, we can cast safely
            if (list_b[static_cast<typename std::vector<T>::size_type>((i + j))] 
                != list_a[static_cast<typename std::vector<T>::size_type>(j)]) {
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
    if (list_a == list_b) {
        return List_comparison::equal;
    } else if (is_sublist(list_a, list_b)) {
        return List_comparison::sublist;
    } else if (is_sublist(list_b, list_a)) {
        return List_comparison::superlist;
    } else {
        return List_comparison::unequal;
    }
}

}  // namespace sublist
