#pragma once

#include <vector>
#include <algorithm>
#include <cstddef>
#include <initializer_list>

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
        for (size_t i = 0; i <= list_b.size() - list_a.size(); ++i) {
            if (std::equal(list_a.begin(), list_a.end(), list_b.begin() + i)) {
                a_is_sublist = true;
                break;
            }
        }
    }
    
    // Check if A is a superlist of B (A contains B)
    bool a_is_superlist = false;
    if (list_b.empty()) {
        a_is_superlist = true;
    } else if (list_b.size() <= list_a.size()) {
        for (size_t i = 0; i <= list_a.size() - list_b.size(); ++i) {
            if (std::equal(list_b.begin(), list_b.end(), list_a.begin() + i)) {
                a_is_superlist = true;
                break;
            }
        }
    }
    
    if (a_is_sublist) {
        return List_comparison::sublist;
    } else if (a_is_superlist) {
        return List_comparison::superlist;
    } else {
        return List_comparison::unequal;
    }
}

// Overload for initializer_list to help with type deduction
template <typename T>
List_comparison sublist(std::initializer_list<T> list_a, std::initializer_list<T> list_b) {
    return sublist(std::vector<T>(list_a), std::vector<T>(list_b));
}

}  // namespace sublist
