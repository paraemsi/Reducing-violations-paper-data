#include "all_your_base.h"

namespace all_your_base {

std::vector<base_digit_t> convert(base_digit_t input_base, const std::vector<base_digit_t>& digits, base_digit_t output_base)
{
    // Validate bases
    if((input_base < static_cast<base_digit_t>(2)) || (output_base < static_cast<base_digit_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate digits
    if(digits.empty()) {
        return std::vector<base_digit_t>{};
    }
    for(base_digit_t digit : digits) {
        if(digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }

    // Convert input digits to integer value
    std::uint64_t value = 0U;
    for(base_digit_t digit : digits) {
        value = (value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }

    // Special case: value is zero
    if(value == 0U) {
        return std::vector<base_digit_t>{0U};
    }

    // Convert integer value to output base
    std::vector<base_digit_t> result;
    while(value > 0U) {
        base_digit_t remainder = static_cast<base_digit_t>(value % static_cast<std::uint64_t>(output_base));
        result.insert(result.begin(), remainder);
        value = value / static_cast<std::uint64_t>(output_base);
    }

    return result;
}

}  // namespace all_your_base
