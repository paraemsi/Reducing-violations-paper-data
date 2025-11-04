#include "sublist.h"
#include <vector>
#include <cstddef>

namespace sublist {

static bool is_sublist(const std::vector<int>& small, const std::vector<int>& large) {
    if (small.empty()) return true;
    if (small.size() > large.size()) return false;
    for (std::size_t i = 0; i <= large.size() - small.size(); ++i) {
        bool match = true;
        for (std::size_t j = 0; j < small.size(); ++j) {
            if (large[i + j] != small[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    if (a == b) {
        return List_comparison::equal;
    }
    if (is_sublist(a, b)) {
        return List_comparison::sublist;
    }
    if (is_sublist(b, a)) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
