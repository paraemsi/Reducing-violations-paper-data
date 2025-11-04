#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>
#include <stdexcept>

namespace all_your_base {

/* Fixed-width unsigned integer type for all digit/base operations */
using digit_t = std::uint32_t;

/*  Convert a number, expressed by the digit vector `in_digits`
    in the positional base `from_base`,
    into its representation in the positional base `to_base`.

    Preconditions:
    • `from_base` ≥ 2U  and  `to_base` ≥ 2U
    • Every element in `in_digits` is < `from_base`
    • `in_digits` is not empty

    Throws:
    • std::invalid_argument when any precondition is violated
*/
auto convert(digit_t                        from_base,
             const std::vector<digit_t>&    in_digits,
             digit_t                        to_base)
             -> std::vector<digit_t>;

}  // namespace all_your_base

#endif /* ALL_YOUR_BASE_H */
