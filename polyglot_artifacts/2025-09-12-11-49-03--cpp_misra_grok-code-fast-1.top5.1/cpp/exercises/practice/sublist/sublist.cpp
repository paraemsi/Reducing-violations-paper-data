#include "sublist.h"

#include <algorithm>
#include <vector>

namespace sublist {

List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) {
    if ((a == b)) {
        return List_comparison::equal;
    }
    if ((a.empty()) || (std::search(b.begin(), b.end(), a.begin(), a.end()) != b.end())) {
        return List_comparison::sublist;
    }
    if ((b.empty()) || (std::search(a.begin(), a.end(), b.begin(), b.end()) != a.end())) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
