#include "all_your_base.h"

namespace all_your_base {

base_digits_t convert(base_digit_t input_base, const base_digits_t& input_digits, base_digit_t output_base)
{
    // Validate bases
    if((input_base < static_cast<base_digit_t>(2)) || (output_base < static_cast<base_digit_t>(2)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate input digits
    if(input_digits.empty())
    {
        return base_digits_t{};
    }

    // Remove leading zeros
    base_digits_t trimmed_digits = input_digits;
    while((!trimmed_digits.empty()) && (trimmed_digits.front() == static_cast<base_digit_t>(0)))
    {
        trimmed_digits.erase(trimmed_digits.begin());
    }
    if(trimmed_digits.empty())
    {
        return base_digits_t{};
    }

    for(base_digit_t digit : trimmed_digits)
    {
        if(digit >= input_base)
        {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }

    // Convert trimmed_digits to an integer value
    std::uint64_t value = 0U;
    for(base_digit_t digit : trimmed_digits)
    {
        value = (value * input_base) + digit;
    }

    // Special case: value is zero
    if(value == 0U)
    {
        return base_digits_t{};
    }

    // Convert value to output_base
    base_digits_t output_digits;
    while(value > 0U)
    {
        output_digits.insert(output_digits.begin(), static_cast<base_digit_t>(value % output_base));
        value = value / output_base;
    }

    return output_digits;
}

}  // namespace all_your_base
