#pragma once

#include <cstdint>
#include <vector>

namespace sublist {

/*  List_comparison describes the relationship between two lists A and B. */
enum class List_comparison
{
    equal,      /* A == B  */
    sublist,    /* A is contained in B */
    superlist,  /* A contains B */
    unequal     /* none of the above */
};

/*  Determine the relationship between listA and listB. */
auto sublist(const std::vector<std::int32_t>& listA,
             const std::vector<std::int32_t>& listB) -> List_comparison;

}  // namespace sublist
