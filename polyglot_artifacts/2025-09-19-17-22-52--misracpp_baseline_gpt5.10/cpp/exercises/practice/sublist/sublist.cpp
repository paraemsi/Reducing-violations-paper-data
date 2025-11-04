#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept {
    return check(a, b);
}

List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) noexcept {
    return check(std::vector<int>(a), std::vector<int>(b));
}

}  // namespace sublist
