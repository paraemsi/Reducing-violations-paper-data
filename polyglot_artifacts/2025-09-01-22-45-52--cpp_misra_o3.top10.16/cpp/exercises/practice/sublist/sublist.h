#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>

namespace sublist {

/**
 * @brief Enumerates the possible relationships between two lists.
 */
enum class Relation : std::uint8_t
{
    equal     = 0U,
    sublist   = 1U,
    superlist = 2U,
    unequal   = 3U
};

using List_comparison = Relation;

/**
 * @brief Determine the relationship between two lists.
 *
 * @tparam T  Element type (deduced).
 * @param list_a  List A.
 * @param list_b  List B.
 * @return Relation  The relationship of A to B.
 */
/**
 * @brief Check whether 'pattern' occurs as a contiguous sub-sequence of 'data'.
 */
template <typename T>
inline bool is_subsequence(const std::vector<T>& data,
                           const std::vector<T>& pattern)
{
    if (pattern.empty())
    {
        return true;
    }

    const auto it = std::search(data.begin(), data.end(),
                                pattern.begin(), pattern.end());

    return (it != data.end());
}

/**
 * @brief Determine the relationship between two lists A and B.
 */
template <typename T>
inline Relation classify(const std::vector<T>& list_a,
                         const std::vector<T>& list_b)
{
    if (list_a == list_b)
    {
        return Relation::equal;
    }

    const bool a_is_sub { is_subsequence(list_b, list_a) };
    const bool b_is_sub { is_subsequence(list_a, list_b) };

    if ((a_is_sub) && (!b_is_sub))
    {
        return Relation::sublist;
    }

    if ((!a_is_sub) && (b_is_sub))
    {
        return Relation::superlist;
    }

    return Relation::unequal;
}

/**
 * @brief Wrapper required by the Exercism test-suite.
 *
 * This function keeps the original implementation in `classify` but
 * exposes the expected symbol name `sublist::sublist`.
 */
template <typename T>
inline List_comparison sublist(const std::vector<T>& list_a,
                               const std::vector<T>& list_b)
{
    return classify(list_a, list_b);
}

}  // namespace sublist
