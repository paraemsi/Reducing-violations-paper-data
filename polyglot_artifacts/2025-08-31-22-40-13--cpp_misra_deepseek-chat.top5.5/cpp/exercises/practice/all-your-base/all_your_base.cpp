#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits,
                                   std::uint32_t output_base) {
    // Check for valid bases
    if (input_base < 2) {
        throw std::invalid_argument("Input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("Output base must be >= 2");
    }
    
    // Check if all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Handle empty input digits
    if (input_digits.empty()) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert to a numerical value
    std::uint64_t value = 0;
    for (const auto& digit : input_digits) {
        value = (value * input_base) + digit;
    }
    
    // If value is zero, return empty vector
    if (value == 0) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert to output base
    std::vector<std::uint32_t> output_digits;
    while (value > 0) {
        output_digits.insert(output_digits.begin(), value % output_base);
        value /= output_base;
    }
    
    return output_digits;
}

}  // namespace all_your_base
