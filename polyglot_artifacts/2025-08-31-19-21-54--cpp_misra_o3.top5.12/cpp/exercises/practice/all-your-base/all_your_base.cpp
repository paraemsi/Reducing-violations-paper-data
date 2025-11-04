#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

auto convert(digit_t input_base,
             const std::vector<digit_t>& digits,
             digit_t output_base) -> std::vector<digit_t>
{
    /* Validate bases */
    if((input_base < static_cast<digit_t>(2U)) || (output_base < static_cast<digit_t>(2U)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /* Ensure digits are provided */
    if(digits.empty())
    {
        throw std::invalid_argument("Empty digit sequence");
    }

    /* Validate each digit and detect all-zero input */
    bool all_zero = true;
    for(digit_t d : digits)
    {
        if(d >= input_base)
        {
            throw std::invalid_argument("Digit out of range for input base");
        }
        if(d != static_cast<digit_t>(0U))
        {
            all_zero = false;
        }
    }

    if(all_zero)
    {
        return {static_cast<digit_t>(0U)};
    }

    /* Convert to an intermediate unsigned 64-bit value */
    std::uint64_t value = static_cast<std::uint64_t>(0U);
    for(digit_t d : digits)
    {
        value = ((value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(d));
    }

    /* Produce output digits */
    std::vector<digit_t> result;
    while(value > static_cast<std::uint64_t>(0U))
    {
        digit_t remainder = static_cast<digit_t>((value % static_cast<std::uint64_t>(output_base)));
        result.push_back(remainder);
        value = (value / static_cast<std::uint64_t>(output_base));
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
