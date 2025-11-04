#pragma once

#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison : std::uint8_t
{
    equal,
    sublist,
    superlist,
    unequal
};

List_comparison sublist(const std::vector<int>& listA, const std::vector<int>& listB);

}  // namespace sublist
