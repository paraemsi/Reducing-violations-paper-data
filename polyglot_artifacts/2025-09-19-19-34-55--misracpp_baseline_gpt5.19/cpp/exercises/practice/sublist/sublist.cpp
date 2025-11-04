#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept {
    return check(a, b);
}

}  // namespace sublist
