#pragma once

#include <vector>
#include <cstddef>  // for std::size_t

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };


namespace detail {

// Return true if `small` is a contiguous sub-sequence of `big`
template <typename T>
inline bool contains_sublist(const std::vector<T>& big,
                             const std::vector<T>& small) {
    if (small.empty()) {
        return true;                // empty list is sub-sequence of any list
    }
    if (small.size() > big.size()) {
        return false;
    }
    for (std::size_t i = 0; i <= big.size() - small.size(); ++i) {
        bool match = true;
        for (std::size_t j = 0; j < small.size(); ++j) {
            if (!(big[i + j] == small[j])) {      // use == for generic T
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

}  // namespace detail

List_comparison classify(const std::vector<int>& list_one,
                         const std::vector<int>& list_two) noexcept;

List_comparison sublist(const std::vector<int>& list_one,
                        const std::vector<int>& list_two) noexcept;

}  // namespace sublist
