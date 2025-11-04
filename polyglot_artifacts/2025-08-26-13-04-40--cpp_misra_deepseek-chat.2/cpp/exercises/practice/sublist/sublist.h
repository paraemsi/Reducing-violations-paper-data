#pragma once
#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison {
    equal,
    unequal,
    superlist,
    sublist
};

template <typename T>
List_comparison sublist(const std::vector<T>& list1, const std::vector<T>& list2);

}  // namespace sublist
