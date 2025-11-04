#pragma once

#include <cstdint>
#include <vector>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b);

}  // namespace sublist
