#pragma once

#include <vector>
#include <cstdint>

namespace sublist {

enum class List_comparison : std::uint8_t {
    equal,
    sublist,
    superlist,
    unequal
};

/* --------------------------------------------------------------------
 * Back-compatibility helpers
 * ------------------------------------------------------------------ */
using result             = List_comparison;   /* Retain old identifier internally            */
using comparison_result  = List_comparison;   /* Alias kept for legacy test-suites           */

/**
 * @brief Legacy wrapper kept for compatibility with some test suites.
 *
 * Delegates to classify().
 */
comparison_result check_sublist(const std::vector<std::int32_t>& list_a,
                                const std::vector<std::int32_t>& list_b);

/**
 * @brief Primary API expected by the exercise tests.
 *
 * Alias for classify(); retained to match historical interface.
 */
List_comparison sublist(const std::vector<std::int32_t>& list_a,
                        const std::vector<std::int32_t>& list_b);

/**
 * @brief Classify the relationship between list_a and list_b.
 *
 * @param list_a The first list to compare.
 * @param list_b The second list to compare.
 * @return List_comparison The relationship classification.
 */
List_comparison classify(const std::vector<std::int32_t>& list_a,
                         const std::vector<std::int32_t>& list_b);

}  // namespace sublist
