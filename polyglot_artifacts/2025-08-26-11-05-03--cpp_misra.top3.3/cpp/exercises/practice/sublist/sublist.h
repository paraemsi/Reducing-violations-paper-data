#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

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

List_comparison sublist(const std::vector<value_type>& a, const std::vector<value_type>& b);

}  // namespace sublist
