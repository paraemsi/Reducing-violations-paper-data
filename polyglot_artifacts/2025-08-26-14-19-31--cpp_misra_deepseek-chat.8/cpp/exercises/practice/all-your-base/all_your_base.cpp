#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Check for valid bases first
    if (input_base == 0) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (input_base == 1) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base == 0) {
        throw std::invalid_argument("output base must be >= 2");
    }
    if (output_base == 1) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Handle empty input digits
    if (input_digits.empty()) {
        return {};
    }
    
    // Check if all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert to base 10
    std::uint64_t num = 0;
    for (const auto& digit : input_digits) {
        // Check for potential overflow
        if (num > (UINT64_MAX - digit) / input_base) {
            throw std::overflow_error("number too large to represent");
        }
        num = (num * input_base) + digit;
    }
    
    // If the number is zero, return an empty vector (not {0})
    // This matches the test cases where single_zero and multiple_zeros expect {}
    if (num == 0) {
        return {};
    }
    
    // Convert from base 10 to output base
    std::vector<std::uint32_t> result;
    while (num > 0) {
        result.insert(result.begin(), static_cast<std::uint32_t>(num % output_base));
        num /= output_base;
    }
    
    return result;
}

}  // namespace all_your_base
