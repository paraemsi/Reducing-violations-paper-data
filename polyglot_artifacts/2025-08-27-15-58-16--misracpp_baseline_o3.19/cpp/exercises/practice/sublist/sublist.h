#pragma once

#include <vector>
#include <algorithm>
#include <initializer_list>

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };

template <typename T>
inline bool is_subvector(const std::vector<T>& small,
                         const std::vector<T>& large) {
    if (small.empty()) {
        return true;               // An empty list is a sublist of any list
    }
    if (small.size() > large.size()) {
        return false;
    }
    return std::search(large.begin(), large.end(),
                       small.begin(), small.end()) != large.end();
}


template <typename T = int>
inline List_comparison sublist(std::initializer_list<T> a,
                               std::initializer_list<T> b) {
    return sublist(std::vector<T>(a), std::vector<T>(b));
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a,
                               const std::vector<T>& b) {
    if (a == b) {
        return List_comparison::equal;
    }
    if (is_subvector(a, b)) {
        return List_comparison::sublist;
    }
    if (is_subvector(b, a)) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
