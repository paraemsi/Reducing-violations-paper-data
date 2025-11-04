#include "all_your_base.h"

namespace all_your_base {

auto convert(std::int32_t                 from_base,
             const std::vector<digit_t>&  digits,
             std::int32_t                 to_base) -> std::vector<digit_t>
{
    /* Validate bases */
    if ((from_base <= 1) || (to_base <= 1)) {
        throw std::invalid_argument("Bases must be greater than 1");
    }

    if (digits.empty()) {
        throw std::invalid_argument("Input digit sequence may not be empty");
    }

    /* Convert input digits to an intermediate (base-10) value */
    std::uint64_t value = 0U;
    for (const digit_t digit : digits) {
        if (digit >= static_cast<digit_t>(from_base)) {
            throw std::invalid_argument("Digit out of range for input base");
        }

        value = (value * static_cast<std::uint64_t>(from_base))
              + static_cast<std::uint64_t>(digit);
    }

    /* Zero has a single representation */
    if (value == 0U) {
        return std::vector<digit_t>{ static_cast<digit_t>(0U) };
    }

    /* Convert intermediate value to the target base */
    std::vector<digit_t> result{};
    while (value > 0U) {
        const digit_t remainder =
            static_cast<digit_t>(value % static_cast<std::uint64_t>(to_base));
        result.insert(result.begin(), remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    return result;
}

}  // namespace all_your_base
