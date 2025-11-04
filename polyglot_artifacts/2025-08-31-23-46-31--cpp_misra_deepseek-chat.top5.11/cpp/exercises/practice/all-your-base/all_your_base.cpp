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
        throw std::invalid_argument("Input base must be at least 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("Output base must be at least 2");
    }
    
    // Check if all digits are valid for the input base
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be valid for the input base");
        }
    }
    
    // Convert to base 10 number
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        number = number * input_base + digit;
    }
    
    // Handle zero - return empty vector
    if (number == 0) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert to output base
    std::vector<std::uint32_t> result;
    while (number > 0) {
        result.insert(result.begin(), number % output_base);
        number /= output_base;
    }
    
    return result;
}

}  // namespace all_your_base
