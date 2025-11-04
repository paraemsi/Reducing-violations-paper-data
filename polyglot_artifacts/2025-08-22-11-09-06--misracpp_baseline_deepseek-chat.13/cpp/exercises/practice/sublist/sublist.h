#pragma once
#include <vector>
#include <algorithm>

namespace sublist {

enum class List_comparison {
    equal,
    unequal,
    sublist,
    superlist
};

// Helper function to check if list_b starts at a certain position in list_a
template<typename T>
bool is_sublist_at_index(const std::vector<T>& list_a, const std::vector<T>& list_b, size_t index) {
    if (index + list_b.size() > list_a.size()) {
        return false;
    }
    for (size_t i = 0; i < list_b.size(); ++i) {
        if (list_a[index + i] != list_b[i]) {
            return false;
        }
    }
    return true;
}

// Helper function to check if list_b is a sublist of list_a
template<typename T>
bool is_sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    if (list_b.empty()) return true;
    if (list_a.size() < list_b.size()) return false;
    for (size_t i = 0; i <= list_a.size() - list_b.size(); ++i) {
        if (is_sublist_at_index(list_a, list_b, i)) {
            return true;
        }
    }
    return false;
}

template<typename T>
List_comparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    if (list_a.size() == list_b.size()) {
        // Check if they're equal
        if (std::equal(list_a.begin(), list_a.end(), list_b.begin())) {
            return List_comparison::equal;
        }
    } else if (list_a.size() < list_b.size()) {
        // Check if list_a is a sublist of list_b
        if (is_sublist(list_b, list_a)) {
            return List_comparison::sublist;
        }
    } else { // list_a.size() > list_b.size()
        // Check if list_a is a superlist of list_b (list_b is a sublist of list_a)
        if (is_sublist(list_a, list_b)) {
            return List_comparison::superlist;
        }
    }
    return List_comparison::unequal;
}

}  // namespace sublist
