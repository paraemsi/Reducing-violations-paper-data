#pragma once

#include <cstdint>
#include <vector>

namespace sublist {

/*  Result of comparing two lists A and B.
 *  - Equal      : A and B contain the same elements in the same order
 *  - Sublist    : A is a contiguous sub-sequence of B
 *  - Superlist  : A contains B as a contiguous sub-sequence
 *  - Unequal    : none of the above
 */
enum class Comparison
{
    Equal,
    Sublist,
    Superlist,
    Unequal
};


/*  Classify the relationship between lists |a| and |b|.
 *  The function never throws.
 */
[[nodiscard]] auto classify(const std::vector<std::int32_t>& a,
                            const std::vector<std::int32_t>& b) noexcept -> Comparison;

/*  Enumeration required by the exercism test-suite. Uses lower-case enumerators. */
enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

/*  Exercise API entry-point expected by the tests. */
[[nodiscard]] auto sublist(const std::vector<std::int32_t>& a,
                           const std::vector<std::int32_t>& b) noexcept -> List_comparison;

}  // namespace sublist
