#include "sublist.h"

#include <algorithm>  // std::search
#include <vector>

namespace sublist {

namespace {

/**
 * Return true if `small` occurs as a contiguous subsequence inside `big`.
 */
bool contains_sublist(const std::vector<int>& big,
                      const std::vector<int>& small) {
    if (small.empty()) {
        return true;  // Empty list is contained in any list.
    }
    return std::search(big.begin(), big.end(),
                       small.begin(), small.end()) != big.end();
}

}  // namespace

comparison_result classify(const std::vector<int>& list_a,
                           const std::vector<int>& list_b) {
    // Handle trivial empty-list cases first.
    const bool a_empty = list_a.empty();
    const bool b_empty = list_b.empty();

    if (a_empty && b_empty) {
        return comparison_result::equal;
    }
    if (a_empty) {
        return comparison_result::sublist;   // [] is sublist of any list.
    }
    if (b_empty) {
        return comparison_result::superlist; // Any non-empty list contains [].
    }

    if (list_a.size() == list_b.size()) {
        return (list_a == list_b) ? comparison_result::equal
                                  : comparison_result::unequal;
    }

    if (list_a.size() < list_b.size()) {
        return contains_sublist(list_b, list_a) ? comparison_result::sublist
                                                : comparison_result::unequal;
    }

    // list_a is longer than list_b
    return contains_sublist(list_a, list_b) ? comparison_result::superlist
                                            : comparison_result::unequal;
}

List_comparison sublist(const std::vector<int>& list_a,
                        const std::vector<int>& list_b) {
    return classify(list_a, list_b);
}

}  // namespace sublist
