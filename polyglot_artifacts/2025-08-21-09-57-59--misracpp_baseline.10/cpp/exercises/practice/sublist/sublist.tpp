#pragma once

#include <vector>
#include <cstddef>

namespace sublist {

template <typename T>
static bool is_sublist(const std::vector<T>& small, const std::vector<T>& large) {
    if (small.empty()) return true;
    if (small.size() > large.size()) return false;
    for (size_t i = 0; i <= large.size() - small.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < small.size(); ++j) {
            if (large[i + j] != small[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

template <typename T>
List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b) {
    if (a == b) {
        return List_comparison::equal;
    }
    if (is_sublist(a, b)) {
        return List_comparison::sublist;
    }
    if (is_sublist(b, a)) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
