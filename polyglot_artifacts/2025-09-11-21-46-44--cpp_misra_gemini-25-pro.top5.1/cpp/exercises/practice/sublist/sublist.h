#pragma once

#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

List_comparison sublist(const std::vector<std::int32_t>& list_one,
                        const std::vector<std::int32_t>& list_two);

}  // namespace sublist
