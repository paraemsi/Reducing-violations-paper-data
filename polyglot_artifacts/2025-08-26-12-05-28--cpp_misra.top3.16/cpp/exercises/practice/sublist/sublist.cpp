#include "sublist.h"

namespace sublist {

namespace
{

// Returns true if 'container' contains 'sub' as a contiguous subsequence
bool contains_sublist(const std::vector<Element>& container, const std::vector<Element>& sub)
{
    if(sub.empty())
    {
        return true;
    }
    if(container.size() < sub.size())
    {
        return false;
    }
    for(std::size_t i = 0U; (i + sub.size()) <= container.size(); ++i)
    {
        bool match = true;
        for(std::size_t j = 0U; j < sub.size(); ++j)
        {
            if(container[i + j] != sub[j])
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

auto sublist(const std::vector<Element>& a, const std::vector<Element>& b) -> List_comparison
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
