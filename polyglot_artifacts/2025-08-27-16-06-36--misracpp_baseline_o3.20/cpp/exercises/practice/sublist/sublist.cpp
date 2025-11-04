#include "sublist.h"

#include <algorithm>  // for std::search

namespace sublist {

static bool is_sublist(const std::vector<int>& candidate,
                       const std::vector<int>& container) {
    // An empty sequence is a sub-sequence of every sequence.
    if (candidate.empty()) {
        return true;
    }

    // Use std::search to locate the first occurrence of `candidate` inside
    // `container`. If the iterator returned is not `container.end()`, then
    // `candidate` is a sub-sequence of `container`.
    return std::search(container.begin(), container.end(),
                       candidate.begin(), candidate.end()) != container.end();
}

List_comparison sublist(const std::vector<int>& list_one,
                        const std::vector<int>& list_two) {
    if (list_one == list_two) {
        return List_comparison::equal;
    }
    if (is_sublist(list_one, list_two)) {
        return List_comparison::sublist;
    }
    if (is_sublist(list_two, list_one)) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
