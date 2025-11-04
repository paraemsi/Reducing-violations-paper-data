#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <algorithm>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Check for valid bases
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Handle empty input digits by returning empty list
    if (input_digits.empty()) {
        return std::vector<std::uint32_t>{};
    }
    
    // Check if all input digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert the number to a value
    std::uint64_t num = 0;
    for (const auto& digit : input_digits) {
        num = (num * input_base) + digit;
    }
    
    // If the number is zero, return empty list
    if (num == 0) {
        return std::vector<std::uint32_t>{};
    }
    
    // Convert to output base
    std::vector<std::uint32_t> output_digits;
    while (num > 0) {
        output_digits.push_back(static_cast<std::uint32_t>(num % output_base));
        num /= output_base;
    }
    std::reverse(output_digits.begin(), output_digits.end());
    
    return output_digits;
}

}  // namespace all_your_base
