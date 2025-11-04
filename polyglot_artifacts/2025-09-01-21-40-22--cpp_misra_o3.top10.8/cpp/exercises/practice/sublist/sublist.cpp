#include "sublist.h"

namespace sublist {

auto sublist(const IntList& listA, const IntList& listB) -> List_comparison
{
    return compare(listA, listB);
}

} // namespace sublist
