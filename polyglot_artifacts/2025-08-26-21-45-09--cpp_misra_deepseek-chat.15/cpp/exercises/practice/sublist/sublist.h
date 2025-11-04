#pragma once
#include <vector>
#include <cstdint>
#include <cstddef>

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
    if (list.size() < sublist.size()) {
        return false;
    }
    const std::size_t diff_size = list.size() - sublist.size();
    for (std::size_t i = 0; i <= diff_size; ++i) {
        bool found = true;
        for (std::size_t j = 0; j < sublist.size(); ++j) {
            if (list[(i + j)] != sublist[j]) {
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
    if (list1 == list2) {
        return List_comparison::equal;
    } else if (((list1.size() > list2.size()) && is_sublist(list1, list2))) {
        return List_comparison::superlist;
    } else if (((list2.size() > list1.size()) && is_sublist(list2, list1))) {
        return List_comparison::sublist;
    } else {
        return List_comparison::unequal;
    }
}

}  // namespace sublist
