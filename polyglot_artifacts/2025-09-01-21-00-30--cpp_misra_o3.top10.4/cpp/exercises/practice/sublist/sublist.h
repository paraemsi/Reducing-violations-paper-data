#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include <initializer_list>

namespace sublist {

// Result category for list comparison
enum class result : std::uint8_t
{
    equal,     // A == B
    sublist,   // A  is contained by B
    superlist, // A  contains B
    unequal    // none of the above
};

using List_comparison = result;

// Compare two lists and classify their relationship.
// The function is defined as a template to support any
// value‐type that is `==` comparable.
template <typename T>
inline result classify(const std::vector<T>& list_a,
                       const std::vector<T>& list_b)
{
    // Equal – first, handle the simple full-equality check.
    if ((list_a == list_b))
    {
        return result::equal;
    }

    // Handle cases where one of the lists is empty.
    if (list_b.empty())
    {
        return result::superlist; // non-empty A, empty B
    }
    if (list_a.empty())
    {
        return result::sublist;   // empty A, non-empty B
    }

    // Determine sub/super relationship by size and search.
    if ((list_a.size()) < (list_b.size()))
    {
        const auto pos =
            std::search(list_b.begin(),
                        list_b.end(),
                        list_a.begin(),
                        list_a.end());

        if (pos != list_b.end())
        {
            return result::sublist;
        }
    }
    else if ((list_a.size()) > (list_b.size()))
    {
        const auto pos =
            std::search(list_a.begin(),
                        list_a.end(),
                        list_b.begin(),
                        list_b.end());

        if (pos != list_a.end())
        {
            return result::superlist;
        }
    }

    // None of the earlier tests matched – the lists are unequal.
    return result::unequal;
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& list_a,
                               const std::vector<T>& list_b)
{
    /* Delegate to classify for actual logic. */
    return classify(list_a, list_b);
}

/* Convenience overload so that calls like
 *     sublist::sublist({1, 2, 3}, {1, 2, 3});
 * and
 *     sublist::sublist({}, {});
 * compile without requiring the caller to specify a template argument.
 * The tests exercise exactly this form.
 */
inline List_comparison sublist(std::initializer_list<std::int32_t> list_a,
                               std::initializer_list<std::int32_t> list_b)
{
    const std::vector<std::int32_t> vec_a { list_a };
    const std::vector<std::int32_t> vec_b { list_b };
    return classify(vec_a, vec_b);
}

}  // namespace sublist
