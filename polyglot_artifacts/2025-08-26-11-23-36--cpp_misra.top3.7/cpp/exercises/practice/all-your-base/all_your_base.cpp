#include "all_your_base.h"
#include <stdexcept>

namespace all_your_base {

std::vector<digit_t> convert(digit_t input_base, const std::vector<digit_t>& digits, digit_t output_base)
{
    // Validate bases
    if((input_base < static_cast<digit_t>(2)) || (output_base < static_cast<digit_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Remove leading zeros
    std::vector<digit_t> trimmed_digits = digits;
    while((!trimmed_digits.empty()) && (trimmed_digits.front() == static_cast<digit_t>(0))) {
        trimmed_digits.erase(trimmed_digits.begin());
    }

    // If input is empty after removing leading zeros, return {0}
    if(trimmed_digits.empty()) {
        return {static_cast<digit_t>(0)};
    }

    // Validate digits
    for(std::size_t i = 0U; i < trimmed_digits.size(); ++i) {
        if(trimmed_digits[i] >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }

    // Convert input digits to integer value
    std::uint64_t value = 0U;
    for(std::size_t i = 0U; i < trimmed_digits.size(); ++i) {
        value = (value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(trimmed_digits[i]);
    }

    // Convert integer value to output base
    std::vector<digit_t> result;
    if(value == 0U) {
        result.push_back(static_cast<digit_t>(0));
    } else {
        while(value > 0U) {
            result.insert(result.begin(), static_cast<digit_t>(value % static_cast<std::uint64_t>(output_base)));
            value = value / static_cast<std::uint64_t>(output_base);
        }
    }

    return result;
}

}  // namespace all_your_base
