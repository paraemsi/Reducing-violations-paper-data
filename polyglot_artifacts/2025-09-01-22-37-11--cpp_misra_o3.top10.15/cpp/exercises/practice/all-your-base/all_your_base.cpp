#include "all_your_base.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace {

/* Helper to multiply‐accumulate with explicit casts to avoid
 * implicit integral promotions that might change signedness. */
auto multiply_add(std::uint64_t acc,
                  std::uint32_t base,
                  std::uint32_t digit) -> std::uint64_t
{
    return ((acc * static_cast<std::uint64_t>(base))
            + static_cast<std::uint64_t>(digit));
}

} // unnamed namespace

namespace all_your_base {

auto convert(std::uint32_t input_base,
             const std::vector<std::uint32_t>& input_digits,
             std::uint32_t output_base) -> std::vector<std::uint32_t>
{
    /* Validate bases */
    if ((input_base <= static_cast<std::uint32_t>(1U))
        || (output_base <= static_cast<std::uint32_t>(1U))) {
        throw std::invalid_argument("base must be > 1");
    }

    /* Validate digits and accumulate value */
    std::uint64_t value {static_cast<std::uint64_t>(0U)};
    for (const std::uint32_t digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("digit outside input base");
        }
        value = multiply_add(value, input_base, digit);
    }

    /* Early-return when no digits were supplied */
    if (input_digits.empty()) {
        return std::vector<std::uint32_t>{};
    }

    /* Numerical value equals zero → empty output list */
    if (value == static_cast<std::uint64_t>(0U)) {
        return std::vector<std::uint32_t>{};
    }

    /* Convert to output base */
    std::vector<std::uint32_t> out_digits {};
    while (value > static_cast<std::uint64_t>(0U)) {
        const std::uint32_t remainder {
            static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(output_base))};
        out_digits.push_back(remainder);
        value = value / static_cast<std::uint64_t>(output_base);
    }

    std::reverse(out_digits.begin(), out_digits.end());
    return out_digits;
}

}  // namespace all_your_base
