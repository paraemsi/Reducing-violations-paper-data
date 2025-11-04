#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits,
                                   std::uint32_t output_base) {
    // Check for valid bases
    if (input_base < 2) {
        throw std::invalid_argument("Input base must be at least 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("Output base must be at least 2");
    }
    
    // Check if input digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Handle the case where there are no digits
    if (input_digits.empty()) {
        return {};
    }
    
    // Check if all digits are zero
    bool all_zeros = true;
    for (const auto& digit : input_digits) {
        if (digit != 0) {
            all_zeros = false;
            break;
        }
    }
    if (all_zeros) {
        return {};
    }
    
    // Start with the input digits
    std::vector<std::uint32_t> digits(input_digits.begin(), input_digits.end());
    std::vector<std::uint32_t> result;
    
    // Continue until all digits are zero
    while (!digits.empty()) {
        std::uint64_t remainder = 0;
        std::vector<std::uint32_t> quotient;
        
        // Process each digit to divide by output_base
        for (const auto& digit : digits) {
            std::uint64_t value = (remainder * input_base) + digit;
            std::uint32_t quotient_digit = static_cast<std::uint32_t>(value / output_base);
            remainder = value % output_base;
            
            // Add to quotient if it's not the leading zero
            if (!quotient.empty() || quotient_digit != 0) {
                quotient.push_back(quotient_digit);
            }
        }
        
        // The remainder is the next digit in the result
        result.push_back(static_cast<std::uint32_t>(remainder));
        
        // Update digits to the quotient for next iteration
        digits = std::move(quotient);
    }
    
    // Reverse the result to get the correct order
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
