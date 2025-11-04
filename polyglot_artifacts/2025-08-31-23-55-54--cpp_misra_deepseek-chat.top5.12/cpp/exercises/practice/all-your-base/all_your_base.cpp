#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <limits>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Check for valid bases
    if ((input_base < 2) || (output_base < 2)) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check for valid bases
    if ((input_base < 2) || (output_base < 2)) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check all digits are valid for the input base
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert to base 10 number
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        // Check for overflow during multiplication
        if (number > ((std::numeric_limits<std::uint64_t>::max() - digit) / input_base)) {
            throw std::overflow_error("Number too large to represent");
        }
        number = (number * input_base) + digit;
    }
    
    // Handle the case when number is zero - return empty vector
    if (number == 0) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert to output base
    std::vector<std::uint32_t> output_digits;
    while (number > 0) {
        output_digits.insert(output_digits.begin(), (number % output_base));
        number /= output_base;
    }
    
    return output_digits;
}

}  // namespace all_your_base
