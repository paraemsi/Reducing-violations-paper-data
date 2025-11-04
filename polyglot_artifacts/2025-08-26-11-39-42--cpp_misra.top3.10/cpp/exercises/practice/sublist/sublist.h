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

}  // namespace sublist

// Explicit instantiations for common types (to avoid linker errors)
extern template List_comparison sublist<std::int32_t>(const std::vector<std::int32_t>&, const std::vector<std::int32_t>&);
extern template List_comparison sublist<std::uint32_t>(const std::vector<std::uint32_t>&, const std::vector<std::uint32_t>&);
