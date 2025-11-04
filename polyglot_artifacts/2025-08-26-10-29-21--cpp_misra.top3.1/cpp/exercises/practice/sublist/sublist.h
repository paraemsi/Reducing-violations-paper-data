#pragma once

#include <vector>
#include <cstdint>

namespace sublist {

using index_t = std::uint32_t;

enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b);
List_comparison sublist(const std::vector<std::uint32_t>& a, const std::vector<std::uint32_t>& b);
List_comparison sublist(const std::vector<char>& a, const std::vector<char>& b);

} // namespace sublist
