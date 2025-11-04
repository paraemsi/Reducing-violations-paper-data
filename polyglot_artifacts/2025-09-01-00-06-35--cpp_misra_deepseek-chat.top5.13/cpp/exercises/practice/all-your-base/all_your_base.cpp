#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

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
    
    // Check if all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Handle empty input or all zeros
    // If all digits are zero, return an empty vector
    if (input_digits.empty() || 
        std::all_of(input_digits.begin(), input_digits.end(), [](std::uint32_t d) { return d == 0; })) {
        return {};
    }
    
    // Convert the number to a value by processing each digit
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        number = (number * input_base) + digit;
    }
    
    // Convert the number to the output base
    std::vector<std::uint32_t> output_digits;
    while (number > 0) {
        output_digits.insert(output_digits.begin(), number % output_base);
        number /= output_base;
    }
    
    return output_digits;
}

}  // namespace all_your_base
