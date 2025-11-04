#pragma once

#include <vector>

namespace sublist {

enum class Comparison {
    equal,
    sublist,
    superlist,
    unequal
};

Comparison sublist(const std::vector<int>& a, const std::vector<int>& b);

} // namespace sublist
