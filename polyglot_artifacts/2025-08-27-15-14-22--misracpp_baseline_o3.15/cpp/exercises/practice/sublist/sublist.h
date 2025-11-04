#pragma once

#include <vector>

namespace sublist {

/**
 * Enumeration describing the relationship between two lists.
 */
enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

/**
 * Compare two integer lists and determine their relationship.
 *
 * @param list_a First list to compare.
 * @param list_b Second list to compare.
 * @return comparison enum value describing relationship.
 */
List_comparison sublist(const std::vector<int>& list_a,
                        const std::vector<int>& list_b);

}  // namespace sublist
