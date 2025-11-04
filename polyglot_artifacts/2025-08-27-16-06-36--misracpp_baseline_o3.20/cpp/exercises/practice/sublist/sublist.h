#pragma once

#include <vector>

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };

/*
 * Determine the relationship between two lists.
 *
 * Returns:
 *  - List_comparison::equal      : lists are identical
 *  - List_comparison::sublist    : first list is a sub-sequence of the second
 *  - List_comparison::superlist  : first list contains the second as a sub-sequence
 *  - List_comparison::unequal    : none of the above
 */
List_comparison sublist(const std::vector<int>& list_one,
                        const std::vector<int>& list_two);

}  // namespace sublist
