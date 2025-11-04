#include "sublist.h"
#include <vector>
#include <cstddef>

namespace sublist {

namespace {

// Returns true if 'longer' contains 'shorter' as a contiguous subsequence.
bool contains_sublist(const std::vector<int>& longer, const std::vector<int>& shorter) {
    if (shorter.empty()) return true;
    if (shorter.size() > longer.size()) return false;

    for (size_t i = 0; i <= longer.size() - shorter.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < shorter.size(); ++j) {
            if (longer[i + j] != shorter[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

} // namespace

List_comparison sublist(const std::vector<int>& A, const std::vector<int>& B) {
    if (A == B) {
        return List_comparison::equal;
    }
    if (contains_sublist(A, B)) {
        return List_comparison::superlist;
    }
    if (contains_sublist(B, A)) {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
