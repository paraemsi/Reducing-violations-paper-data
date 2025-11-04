#pragma once

#include <vector>

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };

/**
 * Determine the relationship between two integer lists.
 *
 * @param list_a First list to compare.
 * @param list_b Second list to compare.
 * @return List_comparison::equal      if the lists are identical.
 *         List_comparison::sublist    if list_a is contained within list_b.
 *         List_comparison::superlist  if list_a contains list_b.
 *         List_comparison::unequal    otherwise.
 */
List_comparison sublist(const std::vector<int>& list_a, const std::vector<int>& list_b);

}  // namespace sublist
