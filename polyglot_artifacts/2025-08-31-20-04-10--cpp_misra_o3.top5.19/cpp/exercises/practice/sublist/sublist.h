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

/*
 * Determine the relationship between two lists.
 *
 * Returns:
 *   List_comparison::equal      – lists are identical
 *   List_comparison::sublist    – first  list is a sub-sequence of second
 *   List_comparison::superlist  – first  list contains       the second
 *   List_comparison::unequal    – none of the above
 */
auto sublist(const std::vector<std::int32_t>& listA,
             const std::vector<std::int32_t>& listB) -> List_comparison;

}  // namespace sublist
