#include "sublist.h"
#include <vector>
#include <cstddef>

namespace sublist {

static bool is_sublist(const std::vector<int>& small, const std::vector<int>& big) {
    if (small.empty()) return true;
    if (small.size() > big.size()) return false;
    for (size_t i = 0; i <= big.size() - small.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < small.size(); ++j) {
            if (big[i + j] != small[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

Comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    if (a == b) {
        return Comparison::equal;
    }
    if (is_sublist(a, b)) {
        return Comparison::sublist;
    }
    if (is_sublist(b, a)) {
        return Comparison::superlist;
    }
    return Comparison::unequal;
}

}  // namespace sublist
