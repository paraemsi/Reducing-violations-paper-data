#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

namespace sublist {

/*  Relation that can exist between two lists
 *  Equal      : lists contain exactly the same elements in the same order
 *  Sublist    : first  argument is contained   within the second
 *  Superlist  : first  argument contains       the second
 *  Unequal    : none of the above
 */
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};


/* Forward declaration of the primary template overload */
template <typename T>
[[nodiscard]] List_comparison sublist(const std::vector<T>& listA,
                                      const std::vector<T>& listB);

/*  Convenience overload to accept braced-init lists without requiring
 *  explicit template argument deduction. The brace lists are implicitly
 *  converted to std::vector<element_type> by the vector’s initializer-list
 *  constructor.
 */

/*  Returns the relation between listA and listB as specified above.
 *  The template requires that the contained type supports operator==.
 */
template <typename T>
[[nodiscard]] inline List_comparison sublist(const std::vector<T>& listA,
                                             const std::vector<T>& listB)
{
    /* helper – checks if `small` occurs in `big` as a contiguous subsequence */
    auto is_subsequence = [](const std::vector<T>& small,
                             const std::vector<T>& big) -> bool
    {
        if(small.empty())
        {
            return true;
        }

        if(small.size() > big.size())
        {
            return false;
        }

        const std::size_t limit =
            (big.size() - small.size()) + static_cast<std::size_t>(1U);

        for(std::size_t i = static_cast<std::size_t>(0U); i < limit; ++i)
        {
            bool match = true;

            for(std::size_t j = static_cast<std::size_t>(0U);
                j < small.size();
                ++j)
            {
                if(!(big[i + j] == small[j]))
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
    };

    /* equality must be checked first */
    if(listA == listB)
    {
        return List_comparison::equal;
    }

    if(is_subsequence(listA, listB))
    {
        return List_comparison::sublist;
    }

    if(is_subsequence(listB, listA))
    {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
