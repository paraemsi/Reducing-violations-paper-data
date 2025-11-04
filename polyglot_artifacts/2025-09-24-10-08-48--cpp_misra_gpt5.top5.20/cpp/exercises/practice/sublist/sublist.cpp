#include "sublist.h"

namespace sublist {

List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b)
{
    return check<std::int32_t>(a, b);
}

List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b)
{
    const std::vector<std::int32_t> va(a);
    const std::vector<std::int32_t> vb(b);
    return sublist(va, vb);
}

}  // namespace sublist
