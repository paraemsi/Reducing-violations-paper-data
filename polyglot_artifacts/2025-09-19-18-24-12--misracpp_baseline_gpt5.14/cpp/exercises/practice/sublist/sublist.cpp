#include "sublist.h"

#include <algorithm>
#include <vector>

namespace {
bool is_sublist(const std::vector<int>& needle, const std::vector<int>& haystack) {
    if (needle.empty()) {
        return true;
    }
    auto it = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end());
    return it != haystack.end();
}
}  // namespace

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    return compare(a, b);
}

List_comparison compare(const std::vector<int>& a, const std::vector<int>& b) {
    if (a == b) {
        return List_comparison::equal;
    }
    if (is_sublist(a, b)) {
        return List_comparison::sublist;
    }
    if (is_sublist(b, a)) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

List_comparison classify(const std::vector<int>& a, const std::vector<int>& b) {
    return compare(a, b);
}

}  // namespace sublist
