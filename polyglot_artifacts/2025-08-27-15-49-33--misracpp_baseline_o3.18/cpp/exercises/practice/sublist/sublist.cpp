#include "sublist.h"

namespace sublist {

result classify(const std::vector<int>& list_a,
                const std::vector<int>& list_b) {

    // Equal
    if (list_a == list_b) {
        return result::equal;
    }

    // One of the lists is empty
    if (list_a.empty()) {
        return result::sublist;      // [] is sublist of any non-equal list
    }
    if (list_b.empty()) {
        return result::superlist;    // any non-equal list is super of []
    }

    // Check for sub/super relationship
    if (contains_sublist(list_a, list_b)) {
        return result::superlist;
    }
    if (contains_sublist(list_b, list_a)) {
        return result::sublist;
    }

    // Otherwise unequal
    return result::unequal;
}

// Legacy wrapper expected by tests
List_comparison sublist(const std::vector<int>& a,
                        const std::vector<int>& b) {
    return classify(a, b);
}

}  // namespace sublist
