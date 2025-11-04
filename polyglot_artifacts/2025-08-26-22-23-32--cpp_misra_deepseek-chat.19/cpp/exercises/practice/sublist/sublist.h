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
bool is_sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    const std::uint32_t size1 = static_cast<std::uint32_t>(list1.size());
    const std::uint32_t size2 = static_cast<std::uint32_t>(list2.size());
    
    if (size1 > size2) {
        return false;
    }
    if (size1 == 0U) {
        return true;
    }
    
    const std::uint32_t max_index = (size2 - size1);
    for (std::uint32_t i = 0U; i <= max_index; ++i) {
        bool match = true;
        for (std::uint32_t j = 0U; j < size1; ++j) {
            if (!(list2[(i + j)] == list1[j])) {
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
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    if (list1 == list2) {
        return List_comparison::equal;
    } else if (((list1.size() < list2.size()) && (is_sublist(list1, list2)))) {
        return List_comparison::sublist;
    } else if (((list2.size() < list1.size()) && (is_sublist(list2, list1)))) {
        return List_comparison::superlist;
    } else {
        return List_comparison::unequal;
    }
}

}  // namespace sublist
