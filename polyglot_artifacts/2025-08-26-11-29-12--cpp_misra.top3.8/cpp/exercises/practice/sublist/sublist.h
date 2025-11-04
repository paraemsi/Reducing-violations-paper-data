#pragma once

#include <vector>
#include <cstdint>

namespace sublist {

// Match test suite naming
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

// Function signature as expected by the test suite
template <typename T>
List_comparison sublist(const std::vector<T>& listA, const std::vector<T>& listB);

} // namespace sublist
