#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<digit_t> convert(digit_t input_base, 
                             const std::vector<digit_t>& input_digits,
                             digit_t output_base) {
    // Check if bases are valid
    if (input_base < 2U) {
        throw std::invalid_argument("Input base must be >= 2");
    }
    if (output_base < 2U) {
        throw std::invalid_argument("Output base must be >= 2");
    }
    
    // Check if all digits are valid for the input base
    // Also, handle the case where all digits are zero
    bool all_zeros = true;
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
        if (digit != 0U) {
            all_zeros = false;
        }
    }
    
    // If all digits are zero or input is empty, return empty vector
    if (input_digits.empty() || all_zeros) {
        return std::vector<digit_t>{};
    }
    
    // Convert input digits to a number
    std::uint64_t number = 0U;
    for (const auto& digit : input_digits) {
        number = (number * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }
    
    // Convert number to output base
    std::vector<digit_t> output_digits;
    while (number > 0U) {
        output_digits.insert(output_digits.begin(), static_cast<digit_t>(number % static_cast<std::uint64_t>(output_base)));
        number /= static_cast<std::uint64_t>(output_base);
    }
    
    return output_digits;
}

}  // namespace all_your_base
