#include "sublist.h"

#include <cstdint>
#include <vector>

namespace sublist
{
/* Explicit instantiation for the common int32_t case to generate code in a
 * translation unit while keeping the template definition in the header.
 * Additional instantiations will be produced by the compiler as needed.
 */
template auto compare<std::int32_t>(const std::vector<std::int32_t>&,
                                    const std::vector<std::int32_t>&) -> Comparison;
template auto sublist<std::int32_t>(const std::vector<std::int32_t>&,
                                    const std::vector<std::int32_t>&) -> List_comparison;
} // namespace sublist
