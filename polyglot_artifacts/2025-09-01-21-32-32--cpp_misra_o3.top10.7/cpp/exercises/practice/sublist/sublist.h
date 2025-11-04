#pragma once

#include <algorithm>
#include <cstddef>   // for std::size_t
#include <cstdint>   // fixed-width integer aliases (MISRA compliant)
#include <vector>

namespace sublist {

//! Comparison result for two lists
enum class Comparison
{
    equal,      ///< Lists are identical
    sublist,    ///< First list is contained in the second
    superlist,  ///< First list contains the second
    unequal     ///< No sub-/super-relationship and not equal
};

/* Alias demanded by exercise test-suite ------------------------------------ */
using List_comparison = Comparison;

/**
 * @brief Compare two lists according to the exercise specification.
 *
 * @tparam T Type stored in the std::vector – must be EqualityComparable.
 * @param listA First list
 * @param listB Second list
 * @return Comparison Result of the comparison
 */
template <typename T>
[[nodiscard]] inline auto compare(const std::vector<T>& listA,
                                  const std::vector<T>& listB) -> Comparison
{
    /* Equal size branch ---------------------------------------------------- */
    if ((listA.size() == listB.size()))
    {
        if ((listA == listB))
        {
            return Comparison::equal;
        }
        else
        {
            return Comparison::unequal;
        }
    }

    /* listA smaller → it may be a sublist of listB ------------------------ */
    if (listA.size() < listB.size())
    {
        const auto subPos = std::search(listB.cbegin(),
                                        listB.cend(),
                                        listA.cbegin(),
                                        listA.cend());

        if (subPos != listB.cend())
        {
            return Comparison::sublist;
        }
        else
        {
            return Comparison::unequal;
        }
    }

    /* listA larger → it may be a superlist of listB ------------------------ */
    const auto superPos = std::search(listA.cbegin(),
                                      listA.cend(),
                                      listB.cbegin(),
                                      listB.cend());

    if (superPos != listA.cend())
    {
        return Comparison::superlist;
    }
    else
    {
        return Comparison::unequal;
    }

    /* Fallback to satisfy all control paths – logically unreachable */
    return Comparison::unequal;
}

/* -------------------------------------------------------------------------- */
/* Public wrapper with the exact signature expected by the tests              */
/* -------------------------------------------------------------------------- */
template <typename T>
[[nodiscard]] inline auto sublist(const std::vector<T>& listA,
                                  const std::vector<T>& listB) -> List_comparison
{
    /* Delegates real work to compare() while keeping test signature intact */
    return compare(listA, listB);
}

/* -------------------------------------------------------------------------- */
/* Convenience overload for empty-brace calls in the test-suite               */
/* Accepts std::vector<int> so `{}` can be converted without template args    */
/* -------------------------------------------------------------------------- */
[[nodiscard]] inline auto sublist(const std::vector<int>& listA,
                                  const std::vector<int>& listB) -> List_comparison
{
    return compare(listA, listB);
}

/* -------------------------------------------------------------------------- */
/* Overload accepting raw brace-initialiser lists to exactly match the calls   */
/* used by the exercism test-suite (e.g. `sublist::sublist({}, {1, 2, 3})`).   */
/* -------------------------------------------------------------------------- */
template <typename T>
[[nodiscard]] inline auto sublist(std::initializer_list<T> listAInit,
                                  std::initializer_list<T> listBInit) -> List_comparison
{
    const std::vector<T> listA{listAInit};
    const std::vector<T> listB{listBInit};
    return compare(listA, listB);
}

} // namespace sublist
