#include "sublist.h"

#include <algorithm>
#include <initializer_list>

namespace sublist {

namespace {
bool is_subsequence(const std::vector<int>& candidate, const std::vector<int>& container) {
    if (candidate.empty()) return true;
    if (candidate.size() > container.size()) return false;

    auto it = std::search(container.begin(), container.end(),
                          candidate.begin(), candidate.end());
    return it != container.end();
}
}  // namespace

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    switch (classify(a, b)) {
        case relation::equal: return List_comparison::equal;
        case relation::sublist: return List_comparison::sublist;
        case relation::superlist: return List_comparison::superlist;
        default: return List_comparison::unequal;
    }
}

List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) {
    return sublist(std::vector<int>(a), std::vector<int>(b));
}

relation classify(const std::vector<int>& a, const std::vector<int>& b) {
    if (a == b) return relation::equal;
    if (is_subsequence(a, b)) return relation::sublist;
    if (is_subsequence(b, a)) return relation::superlist;
    return relation::unequal;
}

relation compare(const std::vector<int>& a, const std::vector<int>& b) {
    return classify(a, b);
}

relation check(const std::vector<int>& a, const std::vector<int>& b) {
    return classify(a, b);
}

}  // namespace sublist
