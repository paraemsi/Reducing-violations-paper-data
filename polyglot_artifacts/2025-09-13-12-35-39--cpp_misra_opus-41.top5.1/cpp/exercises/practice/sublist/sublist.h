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

template <typename T>
List_comparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    // Check if lists are equal
    if (list_a == list_b) {
        return List_comparison::equal;
    }
    
    // Check if A is a sublist of B (B contains A)
    bool a_is_sublist = false;
    if (list_a.empty()) {
        a_is_sublist = true;
    } else if (list_a.size() <= list_b.size()) {
        for (std::size_t i = 0; i <= (list_b.size() - list_a.size()); ++i) {
            bool match = true;
            for (std::size_t j = 0; j < list_a.size(); ++j) {
                if (list_b[(i + j)] != list_a[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                a_is_sublist = true;
                break;
            }
        }
    } else {
        // A cannot be a sublist if it's larger than B
        a_is_sublist = false;
    }
    
    // Check if A is a superlist of B (A contains B)
    bool a_is_superlist = false;
    if (list_b.empty()) {
        a_is_superlist = true;
    } else if (list_b.size() <= list_a.size()) {
        for (std::size_t i = 0; i <= (list_a.size() - list_b.size()); ++i) {
            bool match = true;
            for (std::size_t j = 0; j < list_b.size(); ++j) {
                if (list_a[(i + j)] != list_b[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                a_is_superlist = true;
                break;
            }
        }
    } else {
        // A cannot be a superlist if it's smaller than B
        a_is_superlist = false;
    }
    
    // Determine the relationship
    if (a_is_sublist) {
        return List_comparison::sublist;
    } else if (a_is_superlist) {
        return List_comparison::superlist;
    } else {
        return List_comparison::unequal;
    }
}

// Overload to help with type deduction from initializer lists
inline List_comparison sublist(const std::vector<std::int32_t>& list_a, const std::vector<std::int32_t>& list_b) {
    return sublist<std::int32_t>(list_a, list_b);
}

}  // namespace sublist
