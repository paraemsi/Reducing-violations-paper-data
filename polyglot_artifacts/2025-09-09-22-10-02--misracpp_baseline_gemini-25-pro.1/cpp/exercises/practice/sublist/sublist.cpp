#include "sublist.h"
#include <algorithm>

namespace sublist {

namespace {

bool is_sublist(const std::vector<int>& sub, const std::vector<int>& super) {
    if (sub.empty()) {
        return true;
    }
    return std::search(super.begin(), super.end(), sub.begin(), sub.end()) != super.end();
}

} // anonymous namespace

List_comparison sublist(const std::vector<int>& list_a, const std::vector<int>& list_b) {
    if (list_a.size() == list_b.size()) {
        return list_a == list_b ? List_comparison::equal : List_comparison::unequal;
    } else if (list_a.size() < list_b.size()) {
        return is_sublist(list_a, list_b) ? List_comparison::sublist : List_comparison::unequal;
    } else {
        return is_sublist(list_b, list_a) ? List_comparison::superlist : List_comparison::unequal;
    }
}

}  // namespace sublist
