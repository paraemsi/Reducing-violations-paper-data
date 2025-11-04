#pragma once

#include <algorithm>
#include <vector>

namespace sublist {

enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
List_comparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b)
{
    if (list_a == list_b) {
        return List_comparison::equal;
    }

    if (list_a.empty() && !list_b.empty()) {
        return List_comparison::sublist;
    }

    if (list_b.empty() && !list_a.empty()) {
        return List_comparison::superlist;
    }

    // Helper to check if `small` is a contiguous sub-sequence of `large`
    auto contains = [](const auto& large, const auto& small) {
        return std::search(large.begin(), large.end(),
                           small.begin(), small.end()) != large.end();
    };

    if (list_a.size() < list_b.size()) {
        return contains(list_b, list_a) ? List_comparison::sublist
                                        : List_comparison::unequal;
    }

    if (list_a.size() > list_b.size()) {
        return contains(list_a, list_b) ? List_comparison::superlist
                                        : List_comparison::unequal;
    }

    // Lengths are equal but contents differ (equality already checked above)
    return List_comparison::unequal;
}

}  // namespace sublist
