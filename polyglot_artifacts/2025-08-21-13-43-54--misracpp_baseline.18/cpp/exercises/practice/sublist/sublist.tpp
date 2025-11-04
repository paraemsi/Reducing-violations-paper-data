#include <cstddef>
#include <vector>
#include <string>
#include "sublist.h"

namespace sublist {

template <typename T>
static bool is_sublist(const std::vector<T>& small, const std::vector<T>& big) {
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

template <typename T>
Comparison check_lists(const std::vector<T>& a, const std::vector<T>& b) {
    if (a == b) {
        return Comparison::Equal;
    }
    if (is_sublist(a, b)) {
        return Comparison::Sublist;
    }
    if (is_sublist(b, a)) {
        return Comparison::Superlist;
    }
    return Comparison::Unequal;
}

template <typename T>
Comparison sublist(const std::vector<T>& a, const std::vector<T>& b) {
    return check_lists(a, b);
}

}  // namespace sublist
