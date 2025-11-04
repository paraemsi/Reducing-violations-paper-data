#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& input_digits,
                                  unsigned int output_base) {
    // Check for valid bases
    if (input_base < 2U) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2U) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Check all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert to a number
    std::uint64_t number = 0U;
    for (const auto& digit : input_digits) {
        number = (number * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }
    
    // Handle number being 0 - return empty vector
    if (number == 0U) {
        return std::vector<unsigned int>{};
    }
    
    // Convert to output base
    std::vector<unsigned int> output_digits;
    while (number > 0U) {
        // Insert at the beginning
        output_digits.insert(output_digits.begin(), 
                             static_cast<unsigned int>(number % static_cast<std::uint64_t>(output_base)));
        number /= static_cast<std::uint64_t>(output_base);
    }
    
    return output_digits;
}

}  // namespace all_your_base
