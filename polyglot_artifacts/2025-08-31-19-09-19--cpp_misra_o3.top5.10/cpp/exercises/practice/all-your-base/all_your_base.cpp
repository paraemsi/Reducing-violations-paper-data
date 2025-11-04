#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

auto convert(std::uint32_t input_base,
             const std::vector<digit_t>& input_digits,
             std::uint32_t output_base) -> std::vector<digit_t>
{
    /* Validate input and output bases */
    if ((input_base < 2U) || (output_base < 2U)) {
        throw std::invalid_argument("Base must be greater than or equal to 2");
    }

    /* Empty input represents the value zero */
    if (input_digits.empty()) {
        return {static_cast<digit_t>(0U)};
    }

    /* Convert from input base to an intermediate base-10 (uint64_t) value */
    std::uint64_t value = 0U;
    for (digit_t digit : input_digits) {
        if (digit >= static_cast<digit_t>(input_base)) {
            throw std::invalid_argument("Digit out of range for input base");
        }
        value = ((value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit));
    }

    /* Convert the intermediate value to the output base */
    std::vector<digit_t> result{};
    if (value == 0U) {
        return {static_cast<digit_t>(0U)};
    }

    while (value > 0U) {
        const std::uint64_t remainder = value % static_cast<std::uint64_t>(output_base);
        result.push_back(static_cast<digit_t>(remainder));
        value = value / static_cast<std::uint64_t>(output_base);
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
