#include "sublist.h"
#include <vector>
#include <cstddef>

namespace sublist {

// Helper: check if 'small' is a contiguous subvector of 'large'
static bool is_sublist(const std::vector<int>& small, const std::vector<int>& large) {
    if (small.empty()) return true;
    if (small.size() > large.size()) return false;
    for (size_t i = 0; i <= large.size() - small.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < small.size(); ++j) {
            if (large[i + j] != small[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

Comparison sublist(const std::vector<int>& A, const std::vector<int>& B) {
    if (A == B) {
        return Comparison::equal;
    }
    if (is_sublist(A, B)) {
        return Comparison::sublist;
    }
    if (is_sublist(B, A)) {
        return Comparison::superlist;
    }
    return Comparison::unequal;
}

}  // namespace sublist
