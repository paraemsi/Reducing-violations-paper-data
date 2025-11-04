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
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Check if list1 is a sublist of list2
    auto is_sublist = [](const std::vector<T>& sub, const std::vector<T>& super) -> bool {
        if (sub.empty()) {
            return true;
        }
        // Use the same type as vector::size_type
        const typename std::vector<T>::size_type sub_size = sub.size();
        const typename std::vector<T>::size_type super_size = super.size();
        
        if (super_size < sub_size) {
            return false;
        }
        
        // To avoid potential underflow, we need to make sure super_size >= sub_size
        // which is guaranteed by the condition above
        for (typename std::vector<T>::size_type i = 0; i <= (super_size - sub_size); ++i) {
            bool match = true;
            for (typename std::vector<T>::size_type j = 0; j < sub_size; ++j) {
                if (super[(i + j)] != sub[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
        return false;
    };
    
    if (list1 == list2) {
        return List_comparison::equal;
    } else if (is_sublist(list1, list2)) {
        return List_comparison::sublist;
    } else if (is_sublist(list2, list1)) {
        return List_comparison::superlist;
    } else {
        return List_comparison::unequal;
    }
}

// Explicit instantiation for int
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);

}  // namespace sublist
