#pragma once
#include <vector>

namespace sublist {

enum class List_comparison {
    equal,
    unequal,
    superlist,
    sublist
};

template <typename T>
List_comparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b);

}  // namespace sublist
