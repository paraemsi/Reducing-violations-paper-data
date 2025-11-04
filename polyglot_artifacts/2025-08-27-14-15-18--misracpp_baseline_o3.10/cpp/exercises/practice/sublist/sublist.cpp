#include "sublist.h"

#include <algorithm>

namespace sublist {

// Return true if `needle` occurs as a contiguous subsequence of `haystack`
static bool contains(const std::vector<int>& haystack,
                     const std::vector<int>& needle) {
    if (needle.empty()) {
        return true;  // the empty list is a sublist of any list
    }
    if (needle.size() > haystack.size()) {
        return false;
    }
    return std::search(haystack.begin(), haystack.end(),
                       needle.begin(), needle.end()) != haystack.end();
}

List_comparison sublist(const std::vector<int>& list_one,
                        const std::vector<int>& list_two) {

    if (list_one == list_two) {
        return List_comparison::equal;
    }

    if (contains(list_two, list_one)) {
        return List_comparison::sublist;
    }

    if (contains(list_one, list_two)) {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
