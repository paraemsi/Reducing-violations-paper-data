#include "sublist.h"

#include <algorithm>

namespace sublist {

List_comparison sublist(const std::vector<int>& list_one,
                        const std::vector<int>& list_two) {
    // Equal lists
    if (list_one == list_two) {
        return List_comparison::equal;
    }

    // Helper lambda to determine if smaller is a contiguous sub-sequence of bigger
    auto is_subsequence = [](const std::vector<int>& smaller,
                             const std::vector<int>& bigger) {
        // The empty list is a sub-sequence of any list
        if (smaller.empty()) {
            return true;
        }
        return std::search(bigger.begin(), bigger.end(),
                           smaller.begin(), smaller.end()) != bigger.end();
    };

    if (list_one.size() < list_two.size()) {
        return is_subsequence(list_one, list_two) ? List_comparison::sublist
                                                  : List_comparison::unequal;
    }

    if (list_one.size() > list_two.size()) {
        return is_subsequence(list_two, list_one) ? List_comparison::superlist
                                                  : List_comparison::unequal;
    }

    // Same size but not equal → unequal
    return List_comparison::unequal;
}

}  // namespace sublist
