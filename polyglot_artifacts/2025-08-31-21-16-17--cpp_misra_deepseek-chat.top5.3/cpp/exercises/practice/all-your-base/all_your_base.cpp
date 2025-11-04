#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& input_digits,
                                  unsigned int output_base) {
    // Validate bases - they must be at least 2
    if (input_base < 2) {
        throw std::invalid_argument("Input base must be at least 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("Output base must be at least 2");
    }
    
    // Check if input_digits is empty - according to tests, return empty vector
    if (input_digits.empty()) {
        return std::vector<unsigned int>{};
    }
    
    // Validate each digit
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Convert to a number using a 64-bit integer to prevent overflow
    std::uint64_t num = 0;
    for (const auto& digit : input_digits) {
        // Cast to uint64_t to follow the rules
        num = (num * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }
    
    // Handle the case when the number is zero - according to tests, return empty vector
    if (num == 0) {
        return std::vector<unsigned int>{};
    }
    
    // Convert to the output base
    std::vector<unsigned int> result;
    while (num > 0) {
        // Insert the remainder at the beginning
        result.insert(result.begin(), static_cast<unsigned int>(num % static_cast<std::uint64_t>(output_base)));
        num /= static_cast<std::uint64_t>(output_base);
    }
    
    return result;
}

}  // namespace all_your_base
