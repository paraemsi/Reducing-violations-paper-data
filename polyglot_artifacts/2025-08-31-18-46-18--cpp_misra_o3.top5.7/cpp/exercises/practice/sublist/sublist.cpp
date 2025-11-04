#include "sublist.h"

namespace sublist {

/*
 * Determine how listA relates to listB.
 * The implementation respects MISRA operator-precedence and compound-statement rules.
 */
List_comparison sublist(const list_t& listA, const list_t& listB)
{
    /* Delegate to the generic template implementation to avoid code
     * duplication while preserving MISRA-compliant fixed-width types.
     */
    return sublist<std::int32_t>(listA, listB);
}

}  // namespace sublist
