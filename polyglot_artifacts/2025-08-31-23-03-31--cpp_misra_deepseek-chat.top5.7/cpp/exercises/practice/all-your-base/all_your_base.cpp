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
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Handle case where input is empty - according to tests, return empty vector
    if (input_digits.empty()) {
        return std::vector<std::uint32_t>();
    }
    
    // Check all digits are valid for the input base
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert the number from input base to a value
    std::uint64_t num = 0;
    for (const auto& digit : input_digits) {
        num = (num * input_base) + digit;
        // Check for overflow? But the problem doesn't specify, so we'll assume it fits
    }
    
    // Handle zero case - according to tests, return empty vector
    if (num == 0) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert the number to the output base
    std::vector<std::uint32_t> result;
    while (num > 0) {
        result.insert(result.begin(), num % output_base);
        num /= output_base;
    }
    
    return result;
}

}  // namespace all_your_base
