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
    if (list.size() < sublist.size()) {
        return false;
    }
    for (std::uint64_t i = 0; i <= (static_cast<std::uint64_t>(list.size()) - static_cast<std::uint64_t>(sublist.size())); ++i) {
        bool match = true;
        for (std::uint64_t j = 0; j < static_cast<std::uint64_t>(sublist.size()); ++j) {
            if ((list[static_cast<typename std::vector<T>::size_type>(i + j)]) != (sublist[static_cast<typename std::vector<T>::size_type>(j)])) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

template <typename T>
List_comparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    if (list_a.size() == list_b.size()) {
        bool are_equal = true;
        for (std::uint64_t i = 0; i < static_cast<std::uint64_t>(list_a.size()); ++i) {
            if ((list_a[static_cast<typename std::vector<T>::size_type>(i)]) != (list_b[static_cast<typename std::vector<T>::size_type>(i)])) {
                are_equal = false;
                break;
            }
        }
        if (are_equal) {
            return List_comparison::equal;
        }
    }
    
    if (is_sublist(list_a, list_b)) {
        return List_comparison::superlist;
    }
    if (is_sublist(list_b, list_a)) {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
