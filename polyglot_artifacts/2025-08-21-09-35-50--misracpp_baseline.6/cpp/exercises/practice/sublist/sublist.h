#pragma once

#include <vector>

namespace sublist {

enum List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

// Function declarations matching test expectations
List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b);
List_comparison sublist(const std::vector<long>& a, const std::vector<long>& b);
List_comparison sublist(const std::vector<char>& a, const std::vector<char>& b);

}  // namespace sublist
