#pragma once

#include <algorithm>
#include <iterator>
#include <cstdint>
#include <vector>

namespace sublist {

// Result of the comparison between two lists
enum class List_comparison : std::uint8_t {
    equal,
    sublist,
    superlist,
    unequal
};

// Internal alias so the existing implementation can stay unchanged
using result = List_comparison;

/*
 * classify
 * --------
 * Determine the relationship between list_a and list_b.
 * The algorithm follows the specification:
 *   - equal       : both lists contain the same elements in the same order
 *   - sublist     : list_a is contained within list_b
 *   - superlist   : list_a contains list_b
 *   - unequal     : none of the above
 *
 * The function is implemented as a template to support any comparable type.
 * It is header-only to avoid linker issues with templates.
 */
template <typename T>
inline auto classify(const std::vector<T>& list_a,
                     const std::vector<T>& list_b) noexcept -> result
{
    if (list_a == list_b) {
        return result::equal;
    }

    if (list_a.empty()) {
        if (!list_b.empty()) {
            return result::sublist;
        }
        return result::equal;   // both empty – handled above, but keeps logic complete
    }

    if (list_b.empty()) {
        return result::superlist;
    }

    if (list_a.size() < list_b.size()) {
        if (std::search(list_b.begin(),
                        list_b.end(),
                        list_a.begin(),
                        list_a.end()) != list_b.end()) {
            return result::sublist;
        }
        return result::unequal;
    }

    if (list_a.size() > list_b.size()) {
        if (std::search(list_a.begin(),
                        list_a.end(),
                        list_b.begin(),
                        list_b.end()) != list_a.end()) {
            return result::superlist;
        }
        return result::unequal;
    }

    return result::unequal;
}

template <typename T>
inline auto sublist(const std::vector<T>& list_a,
                    const std::vector<T>& list_b) noexcept -> List_comparison
{
    return classify(list_a, list_b);
}

}  // namespace sublist
