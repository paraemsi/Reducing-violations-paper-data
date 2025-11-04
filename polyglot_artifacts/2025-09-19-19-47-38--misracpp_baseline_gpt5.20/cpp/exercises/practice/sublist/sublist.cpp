#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    return check_lists(a, b);
}

}  // namespace sublist
