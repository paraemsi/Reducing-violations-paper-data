#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <functional>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base, 
                                  const std::vector<unsigned int>& input_digits, 
                                  unsigned int output_base) {
    // Check for valid bases
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check if all digits are valid
    for (unsigned int digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must satisfy 0 <= d < input base");
        }
    }
    
    // Handle the case where input has no digits or is zero
    if (input_digits.empty()) {
        return {};
    }
    
    // Check if all digits are zero - according to tests, we should return an empty vector
    bool all_zero = true;
    for (unsigned int digit : input_digits) {
        if (digit != 0) {
            all_zero = false;
            break;
        }
    }
    if (all_zero) {
        return {};
    }
    
    // Convert from input_base to output_base without using a large integer
    std::vector<unsigned int> digits = input_digits;
    std::vector<unsigned int> result;
    
    while (digits.size() > 0) {
        // Perform division of digits by output_base
        unsigned long long remainder = 0;
        std::vector<unsigned int> quotient;
        
        for (unsigned int digit : digits) {
            unsigned long long temp = remainder * input_base + digit;
            unsigned int div = temp / output_base;
            remainder = temp % output_base;
            
            // Push the division result if it's not leading zero or if quotient is not empty
            if (!quotient.empty() || div != 0) {
                quotient.push_back(div);
            }
        }
        
        // The remainder is the next digit in the result (from right to left)
        result.push_back(remainder);
        
        // Update digits to the quotient for next iteration
        digits = std::move(quotient);
    }
    
    // Reverse the result to get the correct order
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
