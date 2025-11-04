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
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Handle empty input
    if (input_digits.empty()) {
        return {};
    }
    
    // Check if all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
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
    
    // Convert to output base by repeatedly dividing by output_base
    std::vector<std::uint32_t> number = input_digits;
    std::vector<std::uint32_t> output_digits;
    
    // While number is not zero
    while (!number.empty()) {
        std::uint32_t remainder = 0;
        std::vector<std::uint32_t> quotient;
        
        // Perform long division
        for (const auto& digit : number) {
            std::uint32_t temp = remainder * input_base + digit;
            std::uint32_t q = temp / output_base;
            remainder = temp % output_base;
            
            // Add to quotient if it's not leading zero or if quotient is not empty
            if (!quotient.empty() || q != 0) {
                quotient.push_back(q);
            }
        }
        
        // The remainder is the next digit in the output
        output_digits.insert(output_digits.begin(), remainder);
        number = std::move(quotient);
    }
    
    return output_digits;
}

}  // namespace all_your_base
