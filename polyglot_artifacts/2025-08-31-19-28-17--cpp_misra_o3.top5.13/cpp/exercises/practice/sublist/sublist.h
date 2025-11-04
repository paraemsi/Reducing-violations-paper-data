#pragma once

#include <cstdint>
#include <vector>

namespace sublist {

enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

auto sublist(const std::vector<std::int32_t>& list_a,
             const std::vector<std::int32_t>& list_b) -> List_comparison;

}  // namespace sublist
