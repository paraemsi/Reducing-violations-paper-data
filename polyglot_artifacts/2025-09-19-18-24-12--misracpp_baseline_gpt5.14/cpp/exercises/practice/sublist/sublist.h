#pragma once

#include <vector>

namespace sublist {

// Relationship classification of two lists.
enum class List_comparison { equal, sublist, superlist, unequal };
using comparison = List_comparison;

// Primary API expected by the tests.
List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b);

// Determine the relationship between lists a and b.
List_comparison compare(const std::vector<int>& a, const std::vector<int>& b);

// Alias function name often used in other tracks/tests.
List_comparison classify(const std::vector<int>& a, const std::vector<int>& b);

}  // namespace sublist
