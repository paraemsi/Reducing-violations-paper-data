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
        throw std::invalid_argument("input base must be at least 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be at least 2");
    }
    
    // Check if input digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Handle the case when there are no input digits
    if (input_digits.empty()) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert the digits to a number
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        number = (number * input_base) + digit;
    }
    
    // If the number is zero, return an empty vector (as per tests)
    if (number == 0) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert the number to digits in the output base
    std::vector<std::uint32_t> output_digits;
    while (number > 0) {
        output_digits.insert(output_digits.begin(), number % output_base);
        number /= output_base;
    }
    
    return output_digits;
}

}  // namespace all_your_base
