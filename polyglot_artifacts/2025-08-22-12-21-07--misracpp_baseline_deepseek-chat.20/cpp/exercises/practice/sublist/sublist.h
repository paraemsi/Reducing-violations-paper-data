#pragma once
#include <vector>
#include <cstddef>

namespace sublist {

enum class List_comparison {
    equal,
    unequal,
    sublist,
    superlist
};

template<typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Handle empty lists first
    if (list1.empty()) {
        if (list2.empty()) {
            return List_comparison::equal;
        } else {
            return List_comparison::sublist;
        }
    } else if (list2.empty()) {
        return List_comparison::superlist;
    }
    
    // Check if they're equal
    if (list1.size() == list2.size()) {
        bool areEqual = true;
        for (size_t i = 0; i < list1.size(); ++i) {
            if (list1[i] != list2[i]) {
                areEqual = false;
                break;
            }
        }
        if (areEqual) {
            return List_comparison::equal;
        }
    }
    
    // Check if list1 is a superlist of list2 (list1 contains list2)
    if (list1.size() > list2.size()) {
        for (size_t i = 0; i <= list1.size() - list2.size(); ++i) {
            bool found = true;
            for (size_t j = 0; j < list2.size(); ++j) {
                if (list1[i + j] != list2[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::superlist;
            }
        }
    }
    
    // Check if list1 is a sublist of list2 (list2 contains list1)
    if (list1.size() < list2.size()) {
        for (size_t i = 0; i <= list2.size() - list1.size(); ++i) {
            bool found = true;
            for (size_t j = 0; j < list1.size(); ++j) {
                if (list2[i + j] != list1[j]) {
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
