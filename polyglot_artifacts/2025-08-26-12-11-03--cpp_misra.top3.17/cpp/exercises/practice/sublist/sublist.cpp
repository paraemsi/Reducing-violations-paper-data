#include "sublist.h"

namespace sublist {

namespace
{

// Returns true if 'longer' contains 'shorter' as a contiguous subsequence
bool contains_sublist(const std::vector<value_type>& longer, const std::vector<value_type>& shorter)
{
    if(shorter.empty())
    {
        return true;
    }
    if(longer.size() < shorter.size())
    {
        return false;
    }
    for(std::size_t i = 0U; (i + shorter.size()) <= longer.size(); ++i)
    {
        bool match = true;
        for(std::size_t j = 0U; j < shorter.size(); ++j)
        {
            if(longer[i + j] != shorter[j])
            {
                match = false;
                break;
            }
        }
        if(match)
        {
            return true;
        }
    }
    return false;
}

} // anonymous namespace

List_comparison sublist(const std::vector<value_type>& a, const std::vector<value_type>& b)
{
    if(a == b)
    {
        return List_comparison::equal;
    }
    if(contains_sublist(a, b))
    {
        return List_comparison::superlist;
    }
    if(contains_sublist(b, a))
    {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
