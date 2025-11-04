#pragma once
#include <vector>
#include <cstdint>
#include <algorithm>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

template<typename T>
List_comparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    // Check if equal
    if (list_a == list_b) {
        return List_comparison::equal;
    }
    
    // Check if list_a is a superlist of list_b (list_b is a sublist of list_a)
    if (list_a.size() > list_b.size()) {
        const std::int64_t a_size = static_cast<std::int64_t>(list_a.size());
        const std::int64_t b_size = static_cast<std::int64_t>(list_b.size());
        for (std::int64_t i = 0; i <= (a_size - b_size); ++i) {
            if (std::equal(list_b.begin(), list_b.end(), list_a.begin() + i)) {
                return List_comparison::superlist;
            }
        }
    } else { 
        if (list_a.size() < list_b.size()) {
            const std::int64_t a_size = static_cast<std::int64_t>(list_a.size());
            const std::int64_t b_size = static_cast<std::int64_t>(list_b.size());
            for (std::int64_t i = 0; i <= (b_size - a_size); ++i) {
                if (std::equal(list_a.begin(), list_a.end(), list_b.begin() + i)) {
                    return List_comparison::sublist;
                }
            }
        }
    }
    
    // If none of the above conditions are met, the lists are unequal
    return List_comparison::unequal;
}

}  // namespace sublist
