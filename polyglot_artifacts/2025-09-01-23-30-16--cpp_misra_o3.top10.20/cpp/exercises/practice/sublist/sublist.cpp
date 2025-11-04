#include "sublist.h"

#include <algorithm>  // for std::search

namespace sublist {

// ---------------------------------------------------------------------------
// Internal helpers
// ---------------------------------------------------------------------------

/**
 * @brief Test whether 'super' contains 'sub' as a contiguous subsequence.
 *
 * Empty 'sub' is considered to be contained in any sequence.
 *
 * @tparam T     value type
 * @param super  candidate super-sequence
 * @param sub    candidate sub-sequence
 * @return true  if 'sub' is found inside 'super'
 */
template <typename T>
static auto contains_subsequence(const List<T>& super, const List<T>& sub) -> bool
{
    if (sub.empty())
    {
        return true;
    }

    if (super.size() < sub.size())
    {
        return false;
    }

    const auto it =
        std::search(super.begin(), super.end(), sub.begin(), sub.end());

    return (it != super.end());
}

// ---------------------------------------------------------------------------
// Public interface implementation
// ---------------------------------------------------------------------------

template <typename T>
auto sublist(const List<T>& list_a, const List<T>& list_b) -> List_comparison
{
    if (list_a == list_b)
    {
        return List_comparison::equal;
    }

    if (contains_subsequence(list_a, list_b))
    {
        return List_comparison::superlist;
    }

    if (contains_subsequence(list_b, list_a))
    {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

// ---------------------------------------------------------------------------
// Explicit template instantiations for the most common element type(s)
// ---------------------------------------------------------------------------

// Feel free to add further explicit instantiations if the code base
// requires additional value types.

template List_comparison sublist<std::int32_t>(const List<std::int32_t>&,
                                               const List<std::int32_t>&);

}  // namespace sublist
