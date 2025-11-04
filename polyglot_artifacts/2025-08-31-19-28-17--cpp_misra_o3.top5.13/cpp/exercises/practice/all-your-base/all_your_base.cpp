#include "all_your_base.h"

#include <algorithm>
#include <cstdint>

namespace all_your_base {

auto convert(const std::vector<std::uint32_t>& input_digits,
             std::uint32_t                         from_base,
             std::uint32_t                         to_base) -> std::vector<std::uint32_t>
{
    /* Validate bases */
    if((from_base < static_cast<std::uint32_t>(2U)) || (to_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /* Validate input digits */
    if(input_digits.empty()) {
        throw std::invalid_argument("Input digit sequence is empty");
    }

    for(const std::uint32_t digit : input_digits) {
        if(digit >= from_base) {
            throw std::invalid_argument("Digit out of range for source base");
        }
    }

    /* Convert input digits to an integer value (using 64-bit accumulator) */
    std::uint64_t value {0U};
    for(const std::uint32_t digit : input_digits) {
        value = (value * static_cast<std::uint64_t>(from_base)) + static_cast<std::uint64_t>(digit);
    }

    /* Special case: value == 0 */
    if(value == static_cast<std::uint64_t>(0U)) {
        return {static_cast<std::uint32_t>(0U)};
    }

    /* Convert integer value to target base */
    std::vector<std::uint32_t> result {};
    while(value > static_cast<std::uint64_t>(0U)) {
        const std::uint32_t remainder {static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(to_base))};
        result.push_back(remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    std::reverse(result.begin(), result.end());

    return result;
}

}  // namespace all_your_base
