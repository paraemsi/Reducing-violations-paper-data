#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace sublist {

// Relationship between two lists
enum class relationship : std::uint8_t
{
    equal,      // lists are identical
    superlist,  // first list contains the second
    sublist,    // first list is contained in the second
    unequal     // none of the above
};

// Public aliases expected by the test-suite
using List_comparison = relationship;         // keep one enum type, expose required name
using element_type    = std::int32_t;         // list element type (alias hides raw 'int')

// Helper – returns true if |larger| contains |smaller| as a contiguous subsequence
template <typename T>
inline auto contains_subsequence(const std::vector<T>& larger,
                                 const std::vector<T>& smaller) -> bool
{
    if(smaller.empty())
    {
        return true;
    }

    const auto it =
        std::search(larger.begin(),
                    larger.end(),
                    smaller.begin(),
                    smaller.end());

    return (it != larger.end());
}

// Classify the relationship between |listA| and |listB|
template <typename T>
inline auto classify(const std::vector<T>& listA,
                     const std::vector<T>& listB) -> relationship
{
    if(listA == listB)
    {
        return relationship::equal;
    }

    if(contains_subsequence(listA, listB))
    {
        return relationship::superlist;
    }

    if(contains_subsequence(listB, listA))
    {
        return relationship::sublist;
    }

    return relationship::unequal;
}

// Wrapper with the exact signature required by the tests
inline auto sublist(const std::vector<element_type>& listA,
                    const std::vector<element_type>& listB) -> List_comparison
{
    return classify(listA, listB);
}

}  // namespace sublist
