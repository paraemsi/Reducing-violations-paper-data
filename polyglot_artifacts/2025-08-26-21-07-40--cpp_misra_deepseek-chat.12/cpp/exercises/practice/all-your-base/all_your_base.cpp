#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Handle invalid bases
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check each digit is valid for the input base
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Handle cases where all digits are zero or input is empty
    // Check if all digits are zero or input is empty
    bool all_zeros = true;
    for (const auto& digit : input_digits) {
        if (digit != 0) {
            all_zeros = false;
            break;
        }
    }
    if (input_digits.empty() || all_zeros) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert the digits to a number
    std::uint64_t num = 0;
    for (const auto& digit : input_digits) {
        num = num * input_base + digit;
    }
    
    // Convert to output base
    std::vector<std::uint32_t> result;
    while (num > 0) {
        result.insert(result.begin(), num % output_base);
        num = num / output_base;
    }
    
    return result;
}

}  // namespace all_your_base
