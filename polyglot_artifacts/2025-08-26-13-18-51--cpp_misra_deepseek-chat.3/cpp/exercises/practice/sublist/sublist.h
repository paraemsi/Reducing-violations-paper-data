#pragma once
#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison {
    equal,
    unequal,
    sublist,
    superlist
};

template <typename T>
bool is_sublist(const std::vector<T>& list, const std::vector<T>& other) {
    if ((list.size() > other.size())) {
        return false;
    }
    if (list.empty()) {
        return true;
    }
    
    for (typename std::vector<T>::size_type i = 0; i <= (other.size() - list.size()); ++i) {
        bool found = true;
        for (typename std::vector<T>::size_type j = 0; j < list.size(); ++j) {
            if ((other[(i + j)] != list[j])) {
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
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    if ((list1 == list2)) {
        return List_comparison::equal;
    } else if (is_sublist(list1, list2)) {
        return List_comparison::sublist;
    } else if (is_sublist(list2, list1)) {
        return List_comparison::superlist;
    } else {
        return List_comparison::unequal;
    }
}

}  // namespace sublist
