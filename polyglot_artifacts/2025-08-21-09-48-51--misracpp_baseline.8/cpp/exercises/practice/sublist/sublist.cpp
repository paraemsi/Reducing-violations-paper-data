#include "sublist.h"
#include <vector>
#include <cstddef>

namespace sublist {

// Helper: check if 'longer' contains 'shorter' as a contiguous subsequence
template <typename T>
bool contains_sublist(const std::vector<T>& longer, const std::vector<T>& shorter) {
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

template <typename T>
List_comparison sublist_impl(const std::vector<T>& A, const std::vector<T>& B) {
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

List_comparison sublist(const std::vector<int>& A, const std::vector<int>& B) {
    return sublist_impl(A, B);
}

}  // namespace sublist
