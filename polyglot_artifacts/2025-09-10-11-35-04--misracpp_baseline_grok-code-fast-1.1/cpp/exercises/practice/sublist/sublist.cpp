#include "sublist.h"
#include <algorithm>

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    if (a == b) {
        return List_comparison::equal;
    }
    if (a.empty()) {
        return List_comparison::sublist;
    }
    if (b.empty()) {
        return List_comparison::superlist;
    }
    // Check if a is a contiguous sublist of b
    auto it = std::search(b.begin(), b.end(), a.begin(), a.end());
    if (it != b.end()) {
        return List_comparison::sublist;
    }
    // Check if b is a contiguous sublist of a
    it = std::search(a.begin(), a.end(), b.begin(), b.end());
    if (it != a.end()) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
