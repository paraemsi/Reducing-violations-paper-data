#include "sublist.h"

#include <cstddef>  // std::size_t

namespace
{
    // Check whether `small` appears as a contiguous subsequence of `big`.
    auto is_subvector(const std::vector<std::int32_t>& small,
                      const std::vector<std::int32_t>& big) -> bool
    {
        if (small.empty())
        {
            return true;
        }

        if (small.size() > big.size())
        {
            return false;
        }

        const std::size_t limit { (big.size() - small.size()) };

        for (std::size_t start { 0U }; start <= limit; ++start)
        {
            bool match { true };

            for (std::size_t offset { 0U }; offset < small.size(); ++offset)
            {
                if (big.at((start + offset)) != small.at(offset))
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                return true;
            }
        }

        return false;
    }
}  // unnamed namespace

namespace sublist {

auto sublist(const std::vector<std::int32_t>& list_a,
             const std::vector<std::int32_t>& list_b) -> List_comparison
{
    if (list_a == list_b)
    {
        return List_comparison::equal;
    }

    if (is_subvector(list_a, list_b))
    {
        return List_comparison::sublist;
    }

    if (is_subvector(list_b, list_a))
    {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
