#pragma once

#include <vector>
#include <cstdint>

namespace sublist {

using value_type = std::int32_t;

// Match test suite naming: List_comparison and sublist function
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

auto sublist(const std::vector<value_type>& a, const std::vector<value_type>& b) -> List_comparison;

}  // namespace sublist
