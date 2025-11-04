#include "sublist.h"
#include <algorithm>  // for completeness, matches use of std::search in header

namespace sublist
{

auto sublist(const std::vector<std::int32_t>& list_a,
             const std::vector<std::int32_t>& list_b) -> List_comparison
{
    return detail::compare_lists(list_a, list_b);
}

} // namespace sublist

