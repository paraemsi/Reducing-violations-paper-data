#include "sublist.h"

namespace sublist {

/*
 * Non-template wrapper required by some test suites that expect a concrete
 * overload operating on std::vector<std::int32_t>. It simply forwards to the
 * generic template function sublist<> declared in the header.
 */
auto sublist(const std::vector<std::int32_t>& list_a,
             const std::vector<std::int32_t>& list_b) -> List_comparison
{
    return ::sublist::sublist<std::int32_t>(list_a, list_b);
}

}  // namespace sublist
