#include "sublist.h"

namespace sublist {

comparison check(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) noexcept
{
    return classify<std::int32_t>(a, b);
}

List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) noexcept
{
    return classify<std::int32_t>(a, b);
}

List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b) noexcept
{
    const std::vector<std::int32_t> va(a);
    const std::vector<std::int32_t> vb(b);
    return classify<std::int32_t>(va, vb);
}

}  // namespace sublist
