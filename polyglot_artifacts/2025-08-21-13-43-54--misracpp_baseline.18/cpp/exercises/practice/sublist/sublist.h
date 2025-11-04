#pragma once

#include <vector>

namespace sublist {

enum class Comparison {
    Equal,
    Sublist,
    Superlist,
    Unequal
};

template <typename T>
Comparison check_lists(const std::vector<T>& a, const std::vector<T>& b);

// Alias for legacy test compatibility
using List_comparison = Comparison;

template <typename T>
Comparison sublist(const std::vector<T>& a, const std::vector<T>& b);

}  // namespace sublist
