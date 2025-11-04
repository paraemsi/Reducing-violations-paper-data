#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base,
                                   const std::vector<std::uint32_t>& input_digits,
                                   std::uint32_t output_base) {
    // Validate input bases
    if (input_base < 2) {
        throw std::invalid_argument("Input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("Output base must be >= 2");
    }
    
    // Handle empty input
    if (input_digits.empty()) {
        return {};
    }
    
    // Validate each digit
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Convert to a number
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        number = (number * input_base) + digit;
    }
    
    // If the number is zero, return an empty vector (no digits)
    if (number == 0) {
        return {};
    }
    
    // Convert to the output base
    std::vector<std::uint32_t> output_digits;
    while (number > 0) {
        output_digits.insert(output_digits.begin(), number % output_base);
        number /= output_base;
    }
    
    return output_digits;
}

}  // namespace all_your_base
