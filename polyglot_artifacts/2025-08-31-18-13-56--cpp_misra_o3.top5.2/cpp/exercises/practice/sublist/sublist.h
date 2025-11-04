#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

namespace sublist {

/*
 * Enumerates the possible relationships between two lists.
 * The underlying type is std::int8_t to comply with fixed-width
 * integer usage required by the MISRA rules supplied.
 */
enum class List_comparison : std::int8_t {
    equal     = 0,
    sublist   = 1,
    superlist = 2,
    unequal   = 3
};

/*
 * Determine the relationship between listA and listB.
 *
 * The function is fully defined in the header because it is a
 * template; this avoids linker issues with separate translation
 * units trying to instantiate the same symbol.
 *
 * Requirements enforced by implementation:
 * - Only standard library facilities are used.
 * - Parentheses clarify operator precedence as required.
 */
template <typename T>
inline List_comparison sublist(const std::vector<T>& listA,
                               const std::vector<T>& listB)
{
    /* Equality check first – quickest exit */
    if(listA == listB) {
        return List_comparison::equal;
    }

    /* Empty-list edge cases */
    if(listA.empty()) {
        return List_comparison::sublist;   /* [] is sublist of any listB (even []) */
    }
    if(listB.empty()) {
        return List_comparison::superlist; /* Non-empty listA is superlist of []   */
    }

    /* Helper lambda – wraps std::search to test whether small is
     * a contiguous subsequence of big. */
    auto is_subsequence = [](const std::vector<T>& small,
                             const std::vector<T>& big) -> bool
    {
        return (std::search(big.cbegin(),
                            big.cend(),
                            small.cbegin(),
                            small.cend()) != big.cend());
    };

    if(is_subsequence(listA, listB)) {
        return List_comparison::sublist;
    }

    if(is_subsequence(listB, listA)) {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

/*
 * Convenience overload to support the test-suite’s brace-initialiser
 * calls such as `sublist::sublist({}, {1, 2, 3})`.  Using an explicit
 * fixed-width element type avoids ambiguity when the first list is
 * empty, while still complying with the MISRA rule that forbids raw
 * ‘int’ in function signatures.
 */
inline List_comparison sublist(const std::vector<std::int32_t>& listA,
                               const std::vector<std::int32_t>& listB)
{
    /* Delegate to the primary template implementation. */
    return sublist<std::int32_t>(listA, listB);
}

}  // namespace sublist
