#pragma once

#include <vector>

namespace sublist {

enum class Comparison {
    equal,
    sublist,
    superlist,
    unequal
};

// Compare two lists A and B according to the rules described.
Comparison sublist(const std::vector<int>& A, const std::vector<int>& B);

}  // namespace sublist
