#pragma once

#include <vector>

namespace sublist {

enum class List_comparison { equal, sublist, superlist, unequal };

/*  Return the relation between list_one and list_two:
    - List_comparison::equal      : lists contain the same elements in the same order
    - List_comparison::sublist    : list_one  is a (contiguous) sub-sequence of list_two
    - List_comparison::superlist  : list_two  is a (contiguous) sub-sequence of list_one
    - List_comparison::unequal    : none of the above
*/
List_comparison sublist(const std::vector<int>& list_one,
                        const std::vector<int>& list_two);

}  // namespace sublist
