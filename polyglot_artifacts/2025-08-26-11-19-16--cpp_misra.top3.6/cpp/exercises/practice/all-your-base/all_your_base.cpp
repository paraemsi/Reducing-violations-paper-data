#include "all_your_base.h"

namespace all_your_base {

std::vector<base_digit_t> convert(base_digit_t input_base, const std::vector<base_digit_t>& digits, base_digit_t output_base)
{
    // Validate bases
    if((input_base < static_cast<base_digit_t>(2)) || (output_base < static_cast<base_digit_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Remove leading zeros
    std::vector<base_digit_t>::const_iterator it = digits.begin();
    while((it != digits.end()) && ((*it) == static_cast<base_digit_t>(0))) {
        ++it;
    }
    std::vector<base_digit_t> clean_digits(it, digits.end());

    // If no digits left, treat as zero
    if(clean_digits.empty()) {
        return {static_cast<base_digit_t>(0)};
    }

    // Validate digits
    for(std::vector<base_digit_t>::const_iterator d = clean_digits.begin(); d != clean_digits.end(); ++d) {
        if((*d) >= input_base) {
            throw std::invalid_argument("All digits must be < input base and >= 0");
        }
    }

    // Convert input digits to integer value
    std::uint64_t value = static_cast<std::uint64_t>(0);
    for(std::vector<base_digit_t>::const_iterator d = clean_digits.begin(); d != clean_digits.end(); ++d) {
        value = (value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(*d);
    }

    // Convert integer value to output base
    std::vector<base_digit_t> result;
    while(value > static_cast<std::uint64_t>(0)) {
        base_digit_t digit = static_cast<base_digit_t>(value % static_cast<std::uint64_t>(output_base));
        result.insert(result.begin(), digit);
        value = value / static_cast<std::uint64_t>(output_base);
    }

    // If result is empty, the number is zero
    if(result.empty()) {
        result.push_back(static_cast<base_digit_t>(0));
    }

    return result;
}

}  // namespace all_your_base
