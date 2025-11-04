#include "sublist.h"
#include <vector>
#include <algorithm>

namespace sublist {

namespace {
    template <typename T>
    bool is_sublist(const std::vector<T>& small, const std::vector<T>& large) {
        if (small.empty()) return true;
        if (small.size() > large.size()) return false;
        for (size_t i = 0; i <= large.size() - small.size(); ++i) {
            if (std::equal(small.begin(), small.end(), large.begin() + i)) {
                return true;
            }
        }
        return false;
    }
}

template <typename T>
Comparison check(const std::vector<T>& a, const std::vector<T>& b) {
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

// Non-template overload for int, as expected by the tests
Comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    return check(a, b);
}

}  // namespace sublist
