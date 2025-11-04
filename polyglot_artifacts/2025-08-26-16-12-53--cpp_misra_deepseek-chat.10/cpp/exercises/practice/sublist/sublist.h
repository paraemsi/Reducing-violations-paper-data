#pragma once
#include <vector>
#include <cstdint>
#include <algorithm>

namespace sublist {

enum class List_comparison {
    equal,
    unequal,
    sublist,
    superlist
};

template <typename T>
bool is_sublist(const std::vector<T>& list, const std::vector<T>& superlist) {
    if (list.empty()) return true;
    
    // Use std::search to find list in superlist
    auto it = std::search(superlist.begin(), superlist.end(), list.begin(), list.end());
    return it != superlist.end();
}

template <typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    if (list1 == list2) {
        return List_comparison::equal;
    } else if (((list1.size() > list2.size()) && (is_sublist(list2, list1)))) {
        return List_comparison::superlist;
    } else if (((list2.size() > list1.size()) && (is_sublist(list1, list2)))) {
        return List_comparison::sublist;
    } else {
        return List_comparison::unequal;
    }
}

}  // namespace sublist
