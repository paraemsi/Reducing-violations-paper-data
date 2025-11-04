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

template <typename T>
List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b);

} // namespace sublist
