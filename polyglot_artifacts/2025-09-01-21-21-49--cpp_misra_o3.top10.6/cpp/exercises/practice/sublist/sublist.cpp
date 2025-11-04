#include "sublist.h"

#include <algorithm>

namespace sublist
{

namespace
{

[[nodiscard]] bool is_subvector(const std::vector<std::int32_t>& small,
                                const std::vector<std::int32_t>& large) noexcept
{
    if (small.empty())
    {
        return true;
    }

    const auto it { std::search(large.cbegin(),
                                large.cend(),
                                small.cbegin(),
                                small.cend()) };

    return (it != large.cend());
}

}  // unnamed namespace

List_comparison sublist(const std::vector<std::int32_t>& list_one,
                        const std::vector<std::int32_t>& list_two) noexcept
{
    if (list_one == list_two)
    {
        return List_comparison::equal;
    }

    if (is_subvector(list_one, list_two))
    {
        return List_comparison::sublist;
    }

    if (is_subvector(list_two, list_one))
    {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
