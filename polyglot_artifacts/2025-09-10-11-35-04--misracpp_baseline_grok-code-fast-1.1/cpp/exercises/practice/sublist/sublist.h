#pragma once

#include <vector>

namespace sublist {

enum class List_comparison { equal, superlist, sublist, unequal };

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b);

}  // namespace sublist
