#include "sublist.h"

#include <cstddef>

namespace sublist {

namespace {

// Return true if 'needle' appears as a contiguous subsequence inside 'haystack'.
bool is_sublist(const std::vector<int>& needle, const std::vector<int>& haystack) {
    if (needle.empty()) {
        return true;  // Empty list is sublist of any list.
    }
    if (needle.size() > haystack.size()) {
        return false;
    }

    // Sliding window comparison.
    for (std::size_t start = 0; start + needle.size() <= haystack.size(); ++start) {
        bool match = true;
        for (std::size_t i = 0; i < needle.size(); ++i) {
            if (haystack[start + i] != needle[i]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

}  // namespace

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
