#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Handle invalid bases
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Check all digits are valid for the input base
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert the number to a value
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        number = (number * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }
    
    // If number is zero, return an empty vector
    if (number == 0) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert to output base
    std::vector<std::uint32_t> result;
    while (number > 0) {
        result.insert(result.begin(), static_cast<std::uint32_t>(number % static_cast<std::uint64_t>(output_base)));
        number /= static_cast<std::uint64_t>(output_base);
    }
    
    return result;
}

}  // namespace all_your_base
