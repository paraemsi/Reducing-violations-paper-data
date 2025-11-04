#pragma once

#include <vector>
#include <cstdint>

namespace sublist {

using index_t = std::uint32_t;

enum class Comparison
{
    equal = 0,
    sublist = 1,
    superlist = 2,
    unequal = 3
};

Comparison sublist(const std::vector<std::int32_t>&, const std::vector<std::int32_t>&);
Comparison sublist(const std::vector<std::uint32_t>&, const std::vector<std::uint32_t>&);

} // namespace sublist
