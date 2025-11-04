#include "sublist.h"
#include <cstddef>

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
List_comparison sublist_impl(const std::vector<T>& a, const std::vector<T>& b) {
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

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    return sublist_impl(a, b);
}
List_comparison sublist(const std::vector<long>& a, const std::vector<long>& b) {
    return sublist_impl(a, b);
}
List_comparison sublist(const std::vector<char>& a, const std::vector<char>& b) {
    return sublist_impl(a, b);
}

}  // namespace sublist
