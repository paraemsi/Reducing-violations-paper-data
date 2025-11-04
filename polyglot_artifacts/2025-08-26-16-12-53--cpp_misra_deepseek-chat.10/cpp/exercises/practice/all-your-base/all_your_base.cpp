#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base, 
                                  const std::vector<unsigned int>& input_digits, 
                                  unsigned int output_base) {
    // Check for valid bases
    if ((input_base < 2) || (output_base < 2)) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check if input digits are valid
    for (unsigned int digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must satisfy 0 <= d < input base");
        }
    }
    
    // Handle empty input
    if (input_digits.empty()) {
        return std::vector<unsigned int>();
    }
    
    // Convert to a number using a 64-bit integer to prevent overflow
    std::uint64_t num = 0;
    for (unsigned int digit : input_digits) {
        num = (num * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }
    
    // If the number is zero, return an empty vector
    if (num == 0) {
        return std::vector<unsigned int>();
    }
    
    // Convert to output base
    std::vector<unsigned int> result;
    while (num > 0) {
        result.push_back(static_cast<unsigned int>(num % static_cast<std::uint64_t>(output_base)));
        num /= static_cast<std::uint64_t>(output_base);
    }
    
    // Reverse to get the correct order
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
