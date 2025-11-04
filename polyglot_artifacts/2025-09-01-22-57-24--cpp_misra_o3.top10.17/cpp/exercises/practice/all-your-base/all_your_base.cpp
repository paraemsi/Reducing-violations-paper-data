#include "all_your_base.h"

#include <algorithm>   // std::reverse
#include <stdexcept>   // std::invalid_argument

namespace all_your_base {

auto convert(digit_t input_base,
             const std::vector<digit_t>& digits,
             digit_t output_base) -> std::vector<digit_t>
{
    if ( (input_base <= static_cast<digit_t>(1)) ||
         (output_base <= static_cast<digit_t>(1)) )
    {
        throw std::invalid_argument("Bases must be greater than 1");
    }

    if (digits.empty())
    {
        throw std::invalid_argument("Digit sequence must contain at least one digit");
    }

    std::uint64_t value = static_cast<std::uint64_t>(0);
    bool has_non_zero_digit = false;

    for (const digit_t d : digits)
    {
        if (d >= input_base)
        {
            throw std::invalid_argument("Digit out of range for input base");
        }

        if (d != static_cast<digit_t>(0))
        {
            has_non_zero_digit = true;
        }

        value = (value * static_cast<std::uint64_t>(input_base)) +
                static_cast<std::uint64_t>(d);
    }

    if (has_non_zero_digit == false)
    {
        return std::vector<digit_t>{static_cast<digit_t>(0)};
    }

    std::vector<digit_t> out_digits;

    while (value > static_cast<std::uint64_t>(0))
    {
        const digit_t remainder =
            static_cast<digit_t>(value %
                                 static_cast<std::uint64_t>(output_base));
        out_digits.push_back(remainder);
        value = value / static_cast<std::uint64_t>(output_base);
    }

    std::reverse(out_digits.begin(), out_digits.end());

    return out_digits;
}

}  // namespace all_your_base
