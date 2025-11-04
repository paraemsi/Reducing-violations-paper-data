#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept {
    if (a == b) return Comparison::equal;
    if (is_subsequence(a, b)) return Comparison::sublist;
    if (is_subsequence(b, a)) return Comparison::superlist;
    return Comparison::unequal;
}

}  // namespace sublist
