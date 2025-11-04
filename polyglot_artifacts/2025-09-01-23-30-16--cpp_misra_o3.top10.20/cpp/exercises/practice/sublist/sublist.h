#pragma once

#include <cstdint>
#include <vector>

namespace sublist {

// ---------------------------------------------------------------------------
// Type aliases
// ---------------------------------------------------------------------------

template <typename T>
using List = std::vector<T>;

// ---------------------------------------------------------------------------
// Enumerations
// ---------------------------------------------------------------------------

enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

// ---------------------------------------------------------------------------
// API
// ---------------------------------------------------------------------------

/**
 * @brief Determine the relationship between two lists.
 *
 * The function classifies the relationship as one of:
 *   - List_comparison::equal     : both lists have identical contents
 *   - List_comparison::sublist   : first list is wholly contained in the second
 *   - List_comparison::superlist : second list is wholly contained in the first
 *   - List_comparison::unequal   : none of the above
 *
 * The comparison is performed using operator== on the contained type.
 *
 * @tparam T   value type stored in the lists
 * @param list_a  first list
 * @param list_b  second list
 * @return List_comparison describing the relationship
 */
template <typename T>
auto sublist(const List<T>& list_a, const List<T>& list_b) -> List_comparison;

// ---------------------------------------------------------------------------
// Explicit extern template declarations to avoid multiple instantiations
// ---------------------------------------------------------------------------

extern template List_comparison sublist<std::int32_t>(const List<std::int32_t>& list_a,
                                                      const List<std::int32_t>& list_b);

}  // namespace sublist
