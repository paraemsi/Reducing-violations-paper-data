#include "all_your_base.h"
#include <stdexcept>

namespace all_your_base {

std::vector<digit_t> convert(digit_t input_base, const std::vector<digit_t>& digits, digit_t output_base)
{
    // Validate bases
    if((input_base < static_cast<digit_t>(2)) || (output_base < static_cast<digit_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate digits
    if(digits.empty()) {
        return std::vector<digit_t>{};
    }
    bool all_zero = true;
    for(std::size_t i = 0U; i < digits.size(); ++i) {
        if(digits[i] >= input_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
        if(digits[i] != static_cast<digit_t>(0)) {
            all_zero = false;
        }
    }
    if(all_zero) {
        return std::vector<digit_t>{static_cast<digit_t>(0)};
    }

    // Convert input digits to integer value
    std::uint64_t value = 0U;
    for(std::size_t i = 0U; i < digits.size(); ++i) {
        value = (value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digits[i]);
    }

    // Convert integer value to output base
    std::vector<digit_t> result;
    while(value > 0U) {
        result.insert(result.begin(), static_cast<digit_t>(value % static_cast<std::uint64_t>(output_base)));
        value = value / static_cast<std::uint64_t>(output_base);
    }

    return result;
}

}  // namespace all_your_base
