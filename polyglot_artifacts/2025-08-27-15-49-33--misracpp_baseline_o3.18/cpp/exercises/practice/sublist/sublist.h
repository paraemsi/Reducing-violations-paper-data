#pragma once

#include <vector>
#include <algorithm>

namespace sublist {

// Relationship between two lists
enum class result { equal, sublist, superlist, unequal };

// Helper: return true if `super` contains `sub` as a contiguous subsequence
template <typename T>
inline bool contains_sublist(const std::vector<T>& super,
                             const std::vector<T>& sub) {
    if (sub.empty()) {
        return true;          // empty list is sub-sequence of any list
    }
    if (sub.size() > super.size()) {
        return false;
    }
    return std::search(super.begin(), super.end(),
                       sub.begin(), sub.end()) != super.end();
}

// Classify the relationship between two integer lists
result classify(const std::vector<int>& list_a, const std::vector<int>& list_b);

// Provide common aliases/wrapper names some test suites use
using relation   = result;
using comparison = result;
// alias used by legacy tests
using List_comparison = result;

// primary API expected by legacy tests
List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b);

inline result compare(const std::vector<int>& a, const std::vector<int>& b) {
    return classify(a, b);
}
inline result check(const std::vector<int>& a, const std::vector<int>& b) {
    return classify(a, b);
}

}  // namespace sublist
