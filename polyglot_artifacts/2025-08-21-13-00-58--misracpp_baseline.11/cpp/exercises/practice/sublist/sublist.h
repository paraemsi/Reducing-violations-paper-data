#pragma once

#include <vector>

namespace sublist {

enum class Comparison {
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
Comparison check(const std::vector<T>& a, const std::vector<T>& b);

Comparison sublist(const std::vector<int>& a, const std::vector<int>& b);

} // namespace sublist
