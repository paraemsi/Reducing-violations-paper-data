#pragma once
#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

List_comparison sublist(const std::vector<std::int32_t>& list1, const std::vector<std::int32_t>& list2);

}  // namespace sublist
