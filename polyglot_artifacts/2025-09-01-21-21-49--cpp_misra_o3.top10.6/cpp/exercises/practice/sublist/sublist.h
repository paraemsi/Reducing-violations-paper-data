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

[[nodiscard]] List_comparison sublist(const std::vector<std::int32_t>& list_one,
                                      const std::vector<std::int32_t>& list_two) noexcept;

}  // namespace sublist
