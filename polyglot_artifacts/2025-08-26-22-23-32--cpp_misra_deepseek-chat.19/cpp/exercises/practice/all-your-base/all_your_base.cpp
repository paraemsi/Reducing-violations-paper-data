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
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Handle empty input digits - return empty list
    if (input_digits.empty()) {
        return std::vector<std::uint32_t>{};
    }
    
    // Check if all input digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert the number to a numerical value
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        number = (number * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
        // Check for overflow? The problem doesn't specify, so we'll assume it fits
    }
    
    // Handle zero - return empty list
    if (number == 0) {
        return std::vector<std::uint32_t>{};
    }
    
    // Convert to output base digits
    std::vector<std::uint32_t> result;
    while (number > 0) {
        result.insert(result.begin(), static_cast<std::uint32_t>(number % static_cast<std::uint64_t>(output_base)));
        number /= static_cast<std::uint64_t>(output_base);
    }
    
    return result;
}

}  // namespace all_your_base
