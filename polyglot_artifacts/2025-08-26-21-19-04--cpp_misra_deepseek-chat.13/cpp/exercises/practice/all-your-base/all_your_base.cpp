#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Check for valid bases
    if ((input_base < 2U) || (output_base < 2U)) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Handle empty input digits - return empty vector
    if (input_digits.empty()) {
        return {};
    }
    
    // Check if all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Convert the number to a value
    std::uint64_t number = 0U;
    for (const auto& digit : input_digits) {
        number = (number * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }
    
    // If the number is zero, return an empty vector (to match test expectations)
    if (number == 0U) {
        return {};
    }
    
    // Convert to the output base
    std::vector<std::uint32_t> result;
    while (number > 0U) {
        result.insert(result.begin(), static_cast<std::uint32_t>(number % static_cast<std::uint64_t>(output_base)));
        number /= static_cast<std::uint64_t>(output_base);
    }
    
    return result;
}

}  // namespace all_your_base
