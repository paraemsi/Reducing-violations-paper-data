#pragma once

#include <vector>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

// Compare two lists A and B according to the rules described.
// (Only explicitly instantiate for int in sublist.cpp)
List_comparison sublist(const std::vector<int>& A, const std::vector<int>& B);

} // namespace sublist
