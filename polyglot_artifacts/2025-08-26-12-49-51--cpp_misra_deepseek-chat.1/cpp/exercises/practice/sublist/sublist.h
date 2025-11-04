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
bool is_sublist(const std::vector<T>& list, const std::vector<T>& sublist) {
    if (sublist.empty()) {
        return true;
    }
    if ((list.size()) < (sublist.size())) {
        return false;
    }
    for (typename std::vector<T>::size_type i = 0; i <= (list.size() - sublist.size()); ++i) {
        bool found = true;
        for (typename std::vector<T>::size_type j = 0; j < sublist.size(); ++j) {
            if ((list[(i + j)]) != (sublist[j])) {
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
    if ((list1.size()) == (list2.size())) {
        bool are_equal = true;
        for (typename std::vector<T>::size_type i = 0; i < list1.size(); ++i) {
            if ((list1[i]) != (list2[i])) {
                are_equal = false;
                break;
            }
        }
        if (are_equal) {
            return List_comparison::equal;
        }
    }
    
    if ((list1.size()) > (list2.size())) {
        if (is_sublist(list1, list2)) {
            return List_comparison::superlist;
        }
    } else {
        if (is_sublist(list2, list1)) {
            return List_comparison::sublist;
        }
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
