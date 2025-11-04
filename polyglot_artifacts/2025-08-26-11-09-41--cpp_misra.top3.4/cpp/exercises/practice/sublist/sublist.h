#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

namespace sublist {

enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
}; /* MISRA C++: enum class should be terminated with a semicolon */

using Element = std::int32_t; /* MISRA C++: type alias for fixed-width integer */

List_comparison sublist(const std::vector<Element>& listA, const std::vector<Element>& listB);

} // namespace sublist
