#include "sublist.h"

#include <cstddef>

namespace sublist {

namespace
{
    bool is_sublist(const std::vector<int>& small, const std::vector<int>& big)
    {
        if (small.empty())
        {
            return true;
        }
        if (small.size() > big.size())
        {
            return false;
        }
        for (std::size_t i = 0U; (i + small.size()) <= big.size(); ++i)
        {
            bool match = true;
            for (std::size_t j = 0U; j < small.size(); ++j)
            {
                if (!(big[i + j] == small[j]))
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
}

List_comparison sublist(const std::vector<int>& listA, const std::vector<int>& listB)
{
    if (listA == listB)
    {
        return List_comparison::equal;
    }
    if (is_sublist(listA, listB))
    {
        return List_comparison::sublist;
    }
    if (is_sublist(listB, listA))
    {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
