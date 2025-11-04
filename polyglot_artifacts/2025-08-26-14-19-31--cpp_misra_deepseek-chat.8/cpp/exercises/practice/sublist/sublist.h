#pragma once
#include <vector>

namespace sublist {

enum class List_comparison {
    equal,
    unequal,
    sublist,
    superlist
};

template <typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2);

}  // namespace sublist
