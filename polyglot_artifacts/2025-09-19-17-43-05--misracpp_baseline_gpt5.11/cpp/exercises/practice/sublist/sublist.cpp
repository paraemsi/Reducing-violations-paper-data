#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept {
    if (a == b) return List_comparison::equal;
    if (contains_subsequence(a, b)) return List_comparison::superlist;
    if (contains_subsequence(b, a)) return List_comparison::sublist;
    return List_comparison::unequal;
}

}  // namespace sublist
