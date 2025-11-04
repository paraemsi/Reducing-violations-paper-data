#include "sublist.h"

namespace sublist {

static bool is_sublist(const ::std::vector<value_type>& small, const ::std::vector<value_type>& big)
{
    if(small.empty())
    {
        return true;
    }
    if(small.size() > big.size())
    {
        return false;
    }
    for(::std::size_t i = 0U; (i + small.size()) <= big.size(); ++i)
    {
        bool match = true;
        for(::std::size_t j = 0U; j < small.size(); ++j)
        {
            if(big[i + j] != small[j])
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

List_comparison sublist(const ::std::vector<value_type>& a, const ::std::vector<value_type>& b)
{
    if(a == b)
    {
        return List_comparison::equal;
    }
    if(is_sublist(a, b))
    {
        return List_comparison::sublist;
    }
    if(is_sublist(b, a))
    {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
