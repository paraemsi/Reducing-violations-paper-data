#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace sublist {

/*
 * Enumeration describing the relationship between two lists.
 * The underlying type is std::uint8_t to keep the enum size explicit
 * without relying on implementation-defined 'int'.
 */
enum class List_comparison : std::uint8_t {
    equal,      // Both lists contain the same elements in the same order
    sublist,    // First list is contained within the second
    superlist,  // First list contains the second
    unequal     // None of the above
};

/*
 * Determine the relationship between two sequences.
 * A templated approach keeps the implementation generic and avoids
 * committing to any particular element type.
 */
template <typename T>
inline List_comparison sublist(const std::vector<T>& first,
                              const std::vector<T>& second)
{
    if (first == second) {
        return List_comparison::equal;
    }

    if (first.empty()) {
        return List_comparison::sublist;
    }

    if (second.empty()) {
        return List_comparison::superlist;
    }

    if (first.size() < second.size()) {
        auto const it = std::search(second.begin(),
                                    second.end(),
                                    first.begin(),
                                    first.end());
        if (it != second.end()) {
            return List_comparison::sublist;
        }
    } else if (first.size() > second.size()) {
        auto const it = std::search(first.begin(),
                                    first.end(),
                                    second.begin(),
                                    second.end());
        if (it != first.end()) {
            return List_comparison::superlist;
        }
    }

    return List_comparison::unequal;
}

}  // namespace sublist
