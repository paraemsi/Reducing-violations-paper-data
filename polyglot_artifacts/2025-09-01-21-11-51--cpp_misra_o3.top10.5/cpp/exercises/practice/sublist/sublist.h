#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

namespace sublist {

using int_t  = std::int32_t;   // fixed-width alias to respect MISRA type-naming rule
using byte_t = std::uint8_t;   // fixed-width alias to respect MISRA type-naming rule

enum class relation : byte_t { equal, sublist, superlist, unequal };
using List_comparison = relation;

/*  Determine the relationship between two lists.
 *  Returns one of: relation::equal, relation::sublist,
 *  relation::superlist, relation::unequal.
 */
[[nodiscard]] auto compare(const std::vector<int_t>& lhs,
                           const std::vector<int_t>& rhs) -> relation;

[[nodiscard]] auto sublist(const std::vector<int_t>& lhs,
                           const std::vector<int_t>& rhs) -> List_comparison;

}  // namespace sublist
