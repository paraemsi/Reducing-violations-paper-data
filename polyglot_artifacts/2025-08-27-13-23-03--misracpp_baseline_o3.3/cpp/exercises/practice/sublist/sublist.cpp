#include "sublist.h"

#include <algorithm>  // std::search
#include <iterator>   // std::begin, std::end

namespace sublist {

List_comparison sublist(const std::vector<int>& lhs, const std::vector<int>& rhs) {
    // 1. Equal
    if (lhs == rhs) {
        return List_comparison::equal;
    }

    // 2. lhs is shorter -> potential sublist
    if (lhs.size() < rhs.size()) {
        auto it = std::search(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
        return it != rhs.end() ? List_comparison::sublist : List_comparison::unequal;
    }

    // 3. lhs is longer -> potential superlist
    if (lhs.size() > rhs.size()) {
        auto it = std::search(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        return it != lhs.end() ? List_comparison::superlist : List_comparison::unequal;
    }

    // Sizes are different and previous checks failed -> unequal
    return List_comparison::unequal;
}

}  // namespace sublist
