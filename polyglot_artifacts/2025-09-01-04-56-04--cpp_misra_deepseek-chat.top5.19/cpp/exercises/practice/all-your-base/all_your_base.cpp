#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Check for valid bases first
    if (input_base < 2) {
        throw std::invalid_argument("Input base must be at least 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("Output base must be at least 2");
    }
    
    // Handle empty input digits
    if (input_digits.empty()) {
        return {};
    }
    
    // Check if all digits are valid for the input base
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Convert to a number
    std::uint64_t num = 0;
    for (const auto& digit : input_digits) {
        num = (num * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }
    
    // If the number is zero, return an empty vector (not {0})
    // This matches the test cases where all zeros should result in empty output
    if (num == 0) {
        return {};
    }
    
    // Convert to output base digits
    std::vector<std::uint32_t> result;
    while (num > 0) {
        result.insert(result.begin(), static_cast<std::uint32_t>(num % static_cast<std::uint64_t>(output_base)));
        num /= static_cast<std::uint64_t>(output_base);
    }
    
    return result;
}

}  // namespace all_your_base
