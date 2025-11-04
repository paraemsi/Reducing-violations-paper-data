#pragma once

#include <vector>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b);

}  // namespace sublist
