#include "sublist.h"

namespace sublist {

namespace {
    template <typename T>
    bool is_sublist(const std::vector<T>& small, const std::vector<T>& big) {
        if (small.empty()) {
            return true;
        }
        if (small.size() > big.size()) {
            return false;
        }
        for (index_t i = 0U; (i + static_cast<index_t>(small.size())) <= static_cast<index_t>(big.size()); ++i) {
            bool match = true;
            for (index_t j = 0U; j < static_cast<index_t>(small.size()); ++j) {
                if (!(big[i + j] == small[j])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
        return false;
    }
}

template <typename T>
Comparison do_compare(const std::vector<T>& listA, const std::vector<T>& listB) {
    if (listA == listB) {
        return Comparison::equal;
    }
    if (is_sublist(listA, listB)) {
        return Comparison::sublist;
    }
    if (is_sublist(listB, listA)) {
        return Comparison::superlist;
    }
    return Comparison::unequal;
}

Comparison sublist(const std::vector<std::int32_t>& listA, const std::vector<std::int32_t>& listB) {
    return do_compare(listA, listB);
}

Comparison sublist(const std::vector<std::uint32_t>& listA, const std::vector<std::uint32_t>& listB) {
    return do_compare(listA, listB);
}

}  // namespace sublist
