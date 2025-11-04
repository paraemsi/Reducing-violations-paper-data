#pragma once

#include <vector>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

/*
 * Compare two integer lists `list_a` and `list_b`.
 *
 * Returns one of:
 *  - Comparison::Equal      : lists contain exactly the same elements in the same order
 *  - Comparison::Sublist    : list_a is contained in list_b
 *  - Comparison::Superlist  : list_a contains list_b
 *  - Comparison::Unequal    : none of the above
 */
List_comparison sublist(const std::vector<int>& list_a, const std::vector<int>& list_b);

}  // namespace sublist
