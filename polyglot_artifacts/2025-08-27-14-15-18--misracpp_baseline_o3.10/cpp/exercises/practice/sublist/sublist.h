#pragma once

#include <vector>

namespace sublist {

// Possible relationships between two lists
enum class List_comparison { equal, sublist, superlist, unequal };

// Classify the relationship between list_one and list_two
List_comparison sublist(const std::vector<int>& list_one,
                        const std::vector<int>& list_two);

}  // namespace sublist
