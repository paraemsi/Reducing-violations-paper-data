#pragma once
#include <vector>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

List_comparison sublist(const std::vector<int>& list1, const std::vector<int>& list2);

}  // namespace sublist
