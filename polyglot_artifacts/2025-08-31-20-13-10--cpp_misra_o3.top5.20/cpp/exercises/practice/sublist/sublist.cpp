#include "sublist.h"
#if 0

namespace
{
/*  helper : return true when the shorter list is a contiguous
 *  sub-sequence of the longer list                                             */
template <typename T>
auto contains_subsequence(const std::vector<T>& long_list,
                          const std::vector<T>& short_list) -> bool
{
    /*  std::search checks for the presence of short_list in long_list          */
    const auto it = std::search(long_list.cbegin(), long_list.cend(),
                                short_list.cbegin(), short_list.cend());
    return (it != long_list.cend());
}
} // unnamed namespace

namespace sublist
{

auto classify(const std::vector<std::int32_t>& list_a,
              const std::vector<std::int32_t>& list_b) -> result
{
    if (list_a == list_b)
    {
        return result::equal;
    }

    if (list_a.empty())
    {
        /*  An empty list is always a sublist of any other list                 */
        return result::sublist;
    }

    if (list_b.empty())
    {
        /*  A non-empty list compared to an empty list is always a superlist    */
        return result::superlist;
    }

    if (list_a.size() < list_b.size())
    {
        if (contains_subsequence(list_b, list_a))
        {
            return result::sublist;
        }
        else
        {
            return result::unequal;
        }
    }

    if (list_a.size() > list_b.size())
    {
        if (contains_subsequence(list_a, list_b))
        {
            return result::superlist;
        }
        else
        {
            return result::unequal;
        }
    }

    /*  Same size but not equal → unequal                                       */
    return result::unequal;
}

} // namespace sublist
#endif /* implementation moved to header */
