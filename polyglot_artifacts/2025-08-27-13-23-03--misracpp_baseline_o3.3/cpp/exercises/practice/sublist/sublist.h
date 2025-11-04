#pragma once

#include <vector>

namespace sublist {

// Relationship between two lists.
enum class List_comparison { equal, sublist, superlist, unequal };

// Determine the relationship between lhs and rhs.
List_comparison sublist(const std::vector<int>& lhs, const std::vector<int>& rhs);

}  // namespace sublist
