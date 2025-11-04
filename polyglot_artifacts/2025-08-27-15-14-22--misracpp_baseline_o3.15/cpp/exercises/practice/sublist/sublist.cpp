#include "sublist.h"

#include <algorithm>

namespace sublist {

namespace {

/**
 * Return true if `candidate` is a contiguous sub-sequence of `source`.
 */
bool is_subsequence(const std::vector<int>& candidate,
                    const std::vector<int>& source)
{
    // An empty list is always a sub-sequence
    if (candidate.empty()) {
        return true;
    }

    return std::search(source.begin(), source.end(),
                       candidate.begin(), candidate.end()) != source.end();
}

} // namespace

List_comparison sublist(const std::vector<int>& list_a,
                        const std::vector<int>& list_b)
{
    if (list_a == list_b) {
        return List_comparison::equal;
    }

    if (is_subsequence(list_a, list_b)) {
        return list_a.size() < list_b.size() ?
               List_comparison::sublist : List_comparison::equal; // equal handled earlier
    }

    if (is_subsequence(list_b, list_a)) {
        return list_b.size() < list_a.size() ?
               List_comparison::superlist : List_comparison::equal; // equal handled earlier
    }

    return List_comparison::unequal;
}

}  // namespace sublist
