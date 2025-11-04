#pragma once
#include <vector>
#include <cstdint>

namespace sublist {

enum class ListComparison {
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
ListComparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    // Check if equal
    if (list_a == list_b) {
        return ListComparison::equal;
    }
    
    // Check if list_a is a superlist of list_b (list_b is a sublist of list_a)
    if (list_a.size() > list_b.size()) {
        const std::uint64_t a_size = static_cast<std::uint64_t>(list_a.size());
        const std::uint64_t b_size = static_cast<std::uint64_t>(list_b.size());
        // An empty list is always a sublist of any list
        if (b_size == 0) {
            return ListComparison::superlist;
        }
        // Check every possible starting position in list_a where list_b could fit
        for (std::uint64_t i = 0; i <= (a_size - b_size); i++) {
            bool match = true;
            for (std::uint64_t j = 0; j < b_size; j++) {
                if (list_a[i + j] != list_b[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return ListComparison::superlist;
            }
        }
    }
    
    // Check if list_a is a sublist of list_b (list_a is found in list_b as a contiguous sequence)
    if (list_a.size() < list_b.size()) {
        const std::uint64_t a_size = static_cast<std::uint64_t>(list_a.size());
        const std::uint64_t b_size = static_cast<std::uint64_t>(list_b.size());
        // An empty list is always a sublist of any list
        if (a_size == 0) {
            return ListComparison::sublist;
        }
        // Check every possible starting position in list_b where list_a could fit
        for (std::uint64_t i = 0; i <= (b_size - a_size); i++) {
            bool match = true;
            for (std::uint64_t j = 0; j < a_size; j++) {
                if (list_b[i + j] != list_a[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return ListComparison::sublist;
            }
        }
    }
    
    // If none of the above conditions are met, the lists are unequal
    return ListComparison::unequal;
}

}  // namespace sublist
