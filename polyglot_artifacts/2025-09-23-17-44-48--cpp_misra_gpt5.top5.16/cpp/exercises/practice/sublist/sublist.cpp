#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b)
{
    if ((a.size() == b.size()) && (std::equal(a.cbegin(), a.cend(), b.cbegin()))) {
        return List_comparison::equal;
    }

    if (detail::contains_subsequence<int>(a, b)) {
        return List_comparison::superlist;
    }

    if (detail::contains_subsequence<int>(b, a)) {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
