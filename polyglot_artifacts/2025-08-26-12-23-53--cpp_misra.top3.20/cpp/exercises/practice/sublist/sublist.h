#pragma once

#include <vector>
#include <cstdint>

namespace sublist {

using value_type = std::int32_t;

// For test compatibility
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

List_comparison sublist(const std::vector<value_type>& listA, const std::vector<value_type>& listB);

}  // namespace sublist
