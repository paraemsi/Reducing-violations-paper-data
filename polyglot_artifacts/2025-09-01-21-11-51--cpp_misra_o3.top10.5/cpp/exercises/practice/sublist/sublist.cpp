#include "sublist.h"
#include <algorithm>

namespace sublist {

namespace
{

/*  Return true if `needle` appears as a contiguous subsequence
 *  within `haystack`.
 */
auto is_contained(const std::vector<int_t>& needle,
                  const std::vector<int_t>& haystack) -> bool
{
    /* An empty sequence is always contained */
    if (needle.empty()) { return true; }

    const auto it = std::search(haystack.cbegin(),
                                haystack.cend(),
                                needle.cbegin(),
                                needle.cend());
    return (it != haystack.cend());
}

} // anonymous namespace

[[nodiscard]] auto compare(const std::vector<int_t>& lhs,
                           const std::vector<int_t>& rhs) -> relation
{
    if (lhs == rhs) { return relation::equal; }

    const std::size_t lhs_size { lhs.size() };
    const std::size_t rhs_size { rhs.size() };

    if (lhs_size < rhs_size)
    {
        return (is_contained(lhs, rhs) ? relation::sublist : relation::unequal);
    }

    if (lhs_size > rhs_size)
    {
        return (is_contained(rhs, lhs) ? relation::superlist : relation::unequal);
    }

    return relation::unequal;
}

[[nodiscard]] auto sublist(const std::vector<int_t>& lhs,
                           const std::vector<int_t>& rhs) -> List_comparison
{
    return compare(lhs, rhs);
}

}  // namespace sublist
