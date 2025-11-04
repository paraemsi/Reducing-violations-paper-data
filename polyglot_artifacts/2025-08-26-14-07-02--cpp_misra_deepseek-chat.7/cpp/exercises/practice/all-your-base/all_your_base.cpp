#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Check if bases are valid
    if (input_base <= 1 || output_base <= 1) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check if all digits are valid for the input base
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must satisfy 0 <= d < input base");
        }
    }
    
    // Handle the case where all digits are leading zeros
    // First, find the first non-zero digit to determine if the number is zero
    bool all_zeros = true;
    for (const auto& digit : input_digits) {
        if (digit != 0) {
            all_zeros = false;
            break;
        }
    }
    
    // If all digits are zero, return an empty vector
    if (all_zeros) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert the number from input base to a value
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        number = (number * input_base) + digit;
    }
    
    // Convert the number to the output base
    std::vector<std::uint32_t> output_digits;
    while (number > 0) {
        output_digits.insert(output_digits.begin(), (number % output_base));
        number /= output_base;
    }
    
    return output_digits;
}

}  // namespace all_your_base
