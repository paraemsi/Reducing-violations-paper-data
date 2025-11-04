#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Handle invalid bases
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check if input digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Handle empty input
    if (input_digits.empty()) {
        return {};
    }
    
    // Handle the case where all digits are zero - according to tests, return empty vector
    bool all_zero = true;
    for (const auto& digit : input_digits) {
        if (digit != 0) {
            all_zero = false;
            break;
        }
    }
    if (all_zero) {
        return {};
    }
    
    // Convert the number from input_base to output_base without using a large intermediate number
    std::vector<std::uint32_t> digits = input_digits;
    std::vector<std::uint32_t> result;
    
    while (!digits.empty()) {
        // Perform division of digits by output_base
        std::uint64_t remainder = 0;
        std::vector<std::uint32_t> quotient;
        
        for (const auto& digit : digits) {
            std::uint64_t temp = (remainder * input_base) + digit;
            std::uint32_t div = static_cast<std::uint32_t>(temp / output_base);
            remainder = temp % output_base;
            
            // Push to quotient if it's not leading zero or if quotient is not empty
            if (!quotient.empty() || div != 0) {
                quotient.push_back(div);
            }
        }
        
        // The remainder is the next digit in the result (in reverse order)
        result.push_back(static_cast<std::uint32_t>(remainder));
        
        // Update digits to the quotient for next iteration
        digits = std::move(quotient);
    }
    
    // Reverse the result to get the correct order
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
