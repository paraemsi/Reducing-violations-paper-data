#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<std::int32_t> & a, const std::vector<std::int32_t> & b)
{
    if ((a == b)) {
        return List_comparison::equal;
    }

    if ((contains_subsequence<std::int32_t>(a, b))) {
        return List_comparison::superlist;
    }

    if ((contains_subsequence<std::int32_t>(b, a))) {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b)
{
    const std::vector<std::int32_t> va(a);
    const std::vector<std::int32_t> vb(b);
    return sublist::sublist(va, vb);
}

}  // namespace sublist
