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

// Declaration only; definition must be in a header for templates
template <typename T>
List_comparison sublist(const std::vector<T>& listA, const std::vector<T>& listB);

} // namespace sublist
