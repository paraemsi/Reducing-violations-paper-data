#pragma once
#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison {
    equal,
    unequal,
    superlist,
    sublist
};

List_comparison sublist(const std::vector<int>& list1, const std::vector<int>& list2);

}  // namespace sublist
