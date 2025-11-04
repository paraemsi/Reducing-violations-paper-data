#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

//--------------------------------------------------------------------
// Helpers
//--------------------------------------------------------------------
static auto to_value(const digits_t& digits,
                     std::int32_t     base) -> std::uint64_t
{
    // Convert the digit sequence to an integral value.
    std::uint64_t value {0U};

    for (digit_t d : digits) {
        value = (value * static_cast<std::uint64_t>(base))
              + static_cast<std::uint64_t>(d);
    }

    return value;
}

static auto from_value(std::uint64_t value,
                       std::int32_t  base) -> digits_t
{
    // Produce digit sequence from an integral value.
    if (value == 0U) {
        return digits_t {static_cast<digit_t>(0U)};
    }

    digits_t result;

    while (value > 0U) {
        std::uint64_t remainder {value % static_cast<std::uint64_t>(base)};
        result.push_back(static_cast<digit_t>(remainder));
        value /= static_cast<std::uint64_t>(base);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

//--------------------------------------------------------------------
// Public API
//--------------------------------------------------------------------
auto convert(std::int32_t     input_base,
             const digits_t&  input_digits,
             std::int32_t     output_base) -> digits_t
{
    // Validate bases
    if ((input_base <= 1) || (output_base <= 1)) {
        throw std::invalid_argument("Bases must be greater than 1");
    }

    // Validate digit list
    if (input_digits.empty()) {
        throw std::invalid_argument("Input digit list must not be empty");
    }

    if ((input_digits.size() > 1U) && (input_digits.front() == 0)) {
        throw std::invalid_argument("Leading zeros are not permitted");
    }

    for (digit_t d : input_digits) {
        if (d >= static_cast<digit_t>(input_base)) {
            throw std::invalid_argument("Digit outside input base range");
        }
    }

    // Perform conversion
    std::uint64_t intermediate {to_value(input_digits, input_base)};
    return from_value(intermediate, output_base);
}

}  // namespace all_your_base
