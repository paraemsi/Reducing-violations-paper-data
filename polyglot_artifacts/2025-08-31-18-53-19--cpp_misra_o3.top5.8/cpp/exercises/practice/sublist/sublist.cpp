#include "sublist.h"

#include <algorithm>   // for std::equal
#include <cstddef>     // for std::size_t

namespace sublist {

namespace {
/**
 * @brief Check whether 'sub' appears as a contiguous subsequence inside 'super'.
 *
 * @param sub   The potential sub-sequence.
 * @param super The list that may contain the sub-sequence.
 * @return true  if 'sub' is a sub-sequence of 'super'.
 * @return false otherwise.
 */
bool is_subsequence(const std::vector<std::int32_t>& sub,
                    const std::vector<std::int32_t>& super)
{
    const std::size_t sub_size   = sub.size();
    const std::size_t super_size = super.size();

    if (sub_size == static_cast<std::size_t>(0U)) {
        /* The empty list is always a sub-sequence. */
        return true;
    }

    if (sub_size > super_size) {
        return false;
    }

    for (std::size_t i = static_cast<std::size_t>(0U);
         (i + sub_size) <= super_size;
         ++i) {
        if (std::equal(sub.begin(),
                       sub.end(),
                       super.begin() + static_cast<std::ptrdiff_t>(i))) {
            return true;
        }
    }
    return false;
}
}  // unnamed namespace

List_comparison classify(const std::vector<std::int32_t>& list_a,
                         const std::vector<std::int32_t>& list_b)
{
    if (list_a == list_b) {
        return List_comparison::equal;
    }

    if (is_subsequence(list_a, list_b)) {
        return List_comparison::sublist;
    }

    if (is_subsequence(list_b, list_a)) {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

/* --------------------------------------------------------------------
 * Back-compatibility helper – delegates to classify()
 * ------------------------------------------------------------------ */
comparison_result check_sublist(const std::vector<std::int32_t>& list_a,
                                const std::vector<std::int32_t>& list_b)
{
    return classify(list_a, list_b);
}

List_comparison sublist(const std::vector<std::int32_t>& list_a,
                        const std::vector<std::int32_t>& list_b)
{
    return classify(list_a, list_b);
}

}  // namespace sublist
