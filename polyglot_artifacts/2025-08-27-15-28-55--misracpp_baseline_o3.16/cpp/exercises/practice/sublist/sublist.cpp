#include "sublist.h"

#include <algorithm>

namespace {

bool is_subsequence(const std::vector<int>& small,
                    const std::vector<int>& big) {
    if (small.empty()) {
        return true;                // Empty list is sub-sequence of any list
    }
    if (small.size() > big.size()) {
        return false;
    }
    auto it = std::search(big.begin(), big.end(),
                          small.begin(), small.end());
    return it != big.end();
}

}  // namespace

namespace sublist {

List_comparison sublist(const std::vector<int>& list_a,
                        const std::vector<int>& list_b) {
    if (list_a == list_b) {
        return List_comparison::equal;
    }
    if (is_subsequence(list_a, list_b)) {
        return List_comparison::sublist;
    }
    if (is_subsequence(list_b, list_a)) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
