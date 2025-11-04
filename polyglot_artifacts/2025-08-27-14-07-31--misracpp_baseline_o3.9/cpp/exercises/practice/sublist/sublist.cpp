#include "sublist.h"

#include <algorithm>  // for std::search
#include <vector>

namespace sublist {

static bool contains(const std::vector<int>& haystack,
                     const std::vector<int>& needle) {
    // An empty sequence is always found.
    if (needle.empty()) {
        return true;
    }
    // std::search returns end iterator if not found.
    return std::search(haystack.begin(), haystack.end(),
                       needle.begin(), needle.end()) != haystack.end();
}

List_comparison sublist(const std::vector<int>& list_a, const std::vector<int>& list_b) {
    if (list_a == list_b) {
        return List_comparison::equal;
    }

    if (list_a.size() < list_b.size()) {
        return contains(list_b, list_a) ? List_comparison::sublist : List_comparison::unequal;
    }

    if (list_a.size() > list_b.size()) {
        return contains(list_a, list_b) ? List_comparison::superlist : List_comparison::unequal;
    }

    // Same size but not equal.
    return List_comparison::unequal;
}

}  // namespace sublist
