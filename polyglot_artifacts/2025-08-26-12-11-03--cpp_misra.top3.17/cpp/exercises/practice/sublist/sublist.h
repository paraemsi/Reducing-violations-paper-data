#pragma once

#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

using value_type = std::int32_t;

List_comparison sublist(const std::vector<value_type>& a, const std::vector<value_type>& b);

} // namespace sublist
