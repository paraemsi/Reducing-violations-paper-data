#pragma once

#include <vector>

namespace sublist {

enum List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

// Compare two lists A and B according to the rules described.
List_comparison sublist(const std::vector<int>&, const std::vector<int>&);

}  // namespace sublist
