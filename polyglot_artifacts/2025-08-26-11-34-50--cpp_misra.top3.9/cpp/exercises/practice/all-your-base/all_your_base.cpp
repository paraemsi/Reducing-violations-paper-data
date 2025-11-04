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
        return std::vector<base_digit_t>{static_cast<base_digit_t>(0)};
    }
    for(const base_digit_t digit : digits) {
        if(digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }

    // Remove leading zeros
    std::size_t first_nonzero = 0U;
    while((first_nonzero < digits.size()) && (digits[first_nonzero] == static_cast<base_digit_t>(0))) {
        ++first_nonzero;
    }
    if(first_nonzero == digits.size()) {
        return std::vector<base_digit_t>{static_cast<base_digit_t>(0)};
    }
    std::vector<base_digit_t> clean_digits(digits.begin() + static_cast<std::ptrdiff_t>(first_nonzero), digits.end());

    // Convert input digits to integer value
    std::uint64_t value = static_cast<std::uint64_t>(0);
    for(const base_digit_t digit : clean_digits) {
        value = (value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }

    // Convert integer value to output base
    std::vector<base_digit_t> result;
    if(value == static_cast<std::uint64_t>(0)) {
        result.push_back(static_cast<base_digit_t>(0));
    } else {
        while(value > static_cast<std::uint64_t>(0)) {
            result.insert(result.begin(), static_cast<base_digit_t>(value % static_cast<std::uint64_t>(output_base)));
            value = value / static_cast<std::uint64_t>(output_base);
        }
    }
    return result;
}

}  // namespace all_your_base
