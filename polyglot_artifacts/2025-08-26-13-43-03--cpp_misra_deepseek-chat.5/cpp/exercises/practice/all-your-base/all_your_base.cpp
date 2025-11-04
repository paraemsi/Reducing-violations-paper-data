#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Check if bases are valid
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Handle empty input digits
    if (input_digits.empty()) {
        return {};
    }
    
    // Check if all digits are valid for the input base
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert the number to base 10 first
    std::uint64_t num = 0;
    for (const auto& digit : input_digits) {
        num = (num * input_base) + digit;
    }
    
    // If the number is zero, return empty vector
    if (num == 0) {
        return {};
    }
    
    // Convert to the output base
    std::vector<std::uint32_t> output_digits;
    while (num > 0) {
        output_digits.insert(output_digits.begin(), num % output_base);
        num /= output_base;
    }
    
    return output_digits;
}

}  // namespace all_your_base
