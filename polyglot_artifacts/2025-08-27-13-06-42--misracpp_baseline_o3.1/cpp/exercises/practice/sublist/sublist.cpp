#include "sublist.h"

namespace sublist {

List_comparison classify(const std::vector<int>& list_one,
                         const std::vector<int>& list_two) noexcept {
    if (list_one == list_two) {
        return List_comparison::equal;
    }
    if (detail::contains_sublist(list_one, list_two)) {
        return List_comparison::superlist;
    }
    if (detail::contains_sublist(list_two, list_one)) {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

List_comparison sublist(const std::vector<int>& list_one,
                        const std::vector<int>& list_two) noexcept {
    return classify(list_one, list_two);
}

}  // namespace sublist
