#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& digits, 
                                   std::uint32_t output_base) {
    // Check if bases are valid
    if (input_base < 2U) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2U) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Check if all digits are valid
    for (const auto& digit : digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert to a numerical value
    std::uint64_t value = 0U;
    for (const auto& digit : digits) {
        value = (value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }
    
    // Handle the case when the number is zero - according to tests, return an empty list
    if (value == 0U) {
        return std::vector<std::uint32_t>{};
    }
    
    // Convert to output base
    std::vector<std::uint32_t> result;
    while (value > 0U) {
        result.insert(result.begin(), static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(output_base)));
        value /= static_cast<std::uint64_t>(output_base);
    }
    
    return result;
}

}  // namespace all_your_base
