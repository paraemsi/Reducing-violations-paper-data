#pragma once

#include <vector>
#include <ostream>

namespace sublist {

enum class comparison_result {
    equal,
    sublist,
    superlist,
    unequal
};

using List_comparison = comparison_result;

inline std::ostream& operator<<(std::ostream& os, List_comparison value) {
    switch (value) {
        case List_comparison::equal:      os << "equal";      break;
        case List_comparison::sublist:    os << "sublist";    break;
        case List_comparison::superlist:  os << "superlist";  break;
        case List_comparison::unequal:    os << "unequal";    break;
    }
    return os;
}

/**
 * Determine the relationship between two integer lists.
 *
 * - equal      : both lists contain the same elements in the same order
 * - sublist    : the first list occurs contiguously inside the second list
 * - superlist  : the second list occurs contiguously inside the first list
 * - unequal    : none of the above
 *
 * @param list_a the first list (A)
 * @param list_b the second list (B)
 * @return comparison_result describing how A relates to B
 */
comparison_result classify(const std::vector<int>& list_a,
                           const std::vector<int>& list_b);

List_comparison sublist(const std::vector<int>& list_a,
                        const std::vector<int>& list_b);

}  // namespace sublist
