#include "sublist.h"

namespace sublist {

List_comparison check(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) noexcept
{
    return (check<std::int32_t>(a, b));
}

List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) noexcept
{
    return (check<std::int32_t>(a, b));
}

}  // namespace sublist
