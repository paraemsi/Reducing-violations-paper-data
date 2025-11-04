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
}; // MISRA C++: enum class should be terminated with a semicolon

using Element = std::int32_t;

auto sublist(const std::vector<Element>& a, const std::vector<Element>& b) -> List_comparison;

} // namespace sublist
