#pragma once

#include <vector>

namespace sublist {

enum class Comparison {
    equal,
    sublist,
    superlist,
    unequal
};

// Only declare the template, do not define it in the header.
template <typename T>
Comparison sublist(const std::vector<T>& a, const std::vector<T>& b);

}  // namespace sublist
