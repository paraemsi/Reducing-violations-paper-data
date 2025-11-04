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

template <typename T>
List_comparison sublist(const std::vector<T>& listA, const std::vector<T>& listB);

} // namespace sublist
