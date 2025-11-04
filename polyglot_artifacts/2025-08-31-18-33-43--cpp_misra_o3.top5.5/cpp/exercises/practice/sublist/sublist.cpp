#include "sublist.h"

#include <algorithm>
#include <iterator>

namespace sublist {

/*  Helper: check if 'inner' appears as a contiguous subsequence of 'outer'. */
static auto is_subsequence(const std::vector<std::int32_t>& outer,
                           const std::vector<std::int32_t>& inner) -> bool
{
    if (inner.empty())
    {
        return true;
    }

    if (outer.size() < inner.size())
    {
        return false;
    }

    /* std::search looks for the first occurrence of inner in outer. */
    const auto it = std::search(outer.cbegin(), outer.cend(),
                                inner.cbegin(), inner.cend());

    return (it != outer.cend());
}

auto sublist(const std::vector<std::int32_t>& listA,
             const std::vector<std::int32_t>& listB) -> List_comparison
{
    if (listA == listB)
    {
        return List_comparison::equal;
    }
    else if (is_subsequence(listA, listB))
    {
        return List_comparison::superlist;
    }
    else if (is_subsequence(listB, listA))
    {
        return List_comparison::sublist;
    }
    else
    {
        return List_comparison::unequal;
    }
}

}  // namespace sublist
