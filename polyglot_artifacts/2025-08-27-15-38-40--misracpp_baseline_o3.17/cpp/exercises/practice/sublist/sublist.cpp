#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<int>& list1,
                        const std::vector<int>& list2) {
    return classify(list1, list2);      // delegates to the template implementation
}

}  // namespace sublist
