#include "sublist.h"

namespace sublist {

// Helper function to check if 'shorter' is a contiguous sublist of 'longer'
static bool is_sublist(const std::vector<Element>& shorter, const std::vector<Element>& longer)
{
    if (shorter.empty())
    {
        return true;
    }
    if (shorter.size() > longer.size())
    {
        return false;
    }
    for (std::size_t i = 0U; (i + shorter.size()) <= longer.size(); ++i)
    {
        bool match = true;
        for (std::size_t j = 0U; j < shorter.size(); ++j)
        {
            if (longer[i + j] != shorter[j])
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

List_comparison sublist(const std::vector<Element>& listA, const std::vector<Element>& listB)
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
