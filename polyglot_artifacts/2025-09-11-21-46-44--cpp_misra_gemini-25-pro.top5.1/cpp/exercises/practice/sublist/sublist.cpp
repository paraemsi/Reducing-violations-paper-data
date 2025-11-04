#include "sublist.h"

#include <algorithm>
#include <vector>

namespace {

bool is_sublist(const std::vector<std::int32_t>& sub, const std::vector<std::int32_t>& main) {
    if (sub.empty()) {
        return true;
    }

    if ((sub.size()) > (main.size())) {
        return false;
    }

    return (std::search(main.begin(), main.end(), sub.begin(), sub.end()) != main.end());
}

} // anonymous namespace

namespace sublist {

List_comparison sublist(const std::vector<std::int32_t>& list_one,
                        const std::vector<std::int32_t>& list_two) {
    if (list_one == list_two) {
        return List_comparison::equal;
    }

    if (is_sublist(list_one, list_two)) {
        return List_comparison::sublist;
    }

    if (is_sublist(list_two, list_one)) {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
