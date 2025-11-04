#pragma once

#include <algorithm>
#include <initializer_list>
#include <vector>

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };
using comparison = List_comparison;
using relation = List_comparison;

template <typename T>
inline bool is_sublist(const std::vector<T>& small, const std::vector<T>& large) {
    if (small.empty()) return true;
    if (small.size() > large.size()) return false;
    auto it = std::search(large.begin(), large.end(), small.begin(), small.end());
    return it != large.end();
}

template <typename T>
inline comparison compare(const std::vector<T>& a, const std::vector<T>& b) {
    if (a == b) return List_comparison::equal;
    if (is_sublist(a, b)) return List_comparison::sublist;
    if (is_sublist(b, a)) return List_comparison::superlist;
    return List_comparison::unequal;
}

template <typename T>
inline relation check(const std::vector<T>& a, const std::vector<T>& b) {
    return compare(a, b);
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b) {
    if (a == b) return List_comparison::equal;
    if (is_sublist(a, b)) return List_comparison::sublist;
    if (is_sublist(b, a)) return List_comparison::superlist;
    return List_comparison::unequal;
}

inline List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) {
    return sublist(std::vector<int>(a), std::vector<int>(b));
}

template <typename T>
inline List_comparison sublist(std::initializer_list<T> a, std::initializer_list<T> b) {
    return sublist(std::vector<T>(a), std::vector<T>(b));
}

}  // namespace sublist
