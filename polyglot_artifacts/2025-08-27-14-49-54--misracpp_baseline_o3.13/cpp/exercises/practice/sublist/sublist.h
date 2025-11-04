#pragma once

#include <vector>
#include <algorithm>

namespace sublist {

// Relationship between two lists.
enum class result { equal, sublist, superlist, unequal };

// Alias expected by some test suites
using comparison = result;

// Enum name expected by the test suite
enum class List_comparison { equal, sublist, superlist, unequal };

// Generic classify function template
template <typename T>
result classify(const std::vector<T>& a, const std::vector<T>& b) {
    // identical
    if (a == b) {
        return result::equal;
    }

    // a shorter: could be sublist
    if (a.size() < b.size()) {
        if (a.empty() ||
            std::search(b.begin(), b.end(), a.begin(), a.end()) != b.end()) {
            return result::sublist;
        }
    }
    // a longer: could be superlist
    else if (a.size() > b.size()) {
        if (b.empty() ||
            std::search(a.begin(), a.end(), b.begin(), b.end()) != a.end()) {
            return result::superlist;
        }
    }

    // none of the above
    return result::unequal;
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a,
                               const std::vector<T>& b) {
    switch (classify(a, b)) {
        case result::equal:
            return List_comparison::equal;
        case result::sublist:
            return List_comparison::sublist;
        case result::superlist:
            return List_comparison::superlist;
        default:
            return List_comparison::unequal;
    }
}

}  // namespace sublist
