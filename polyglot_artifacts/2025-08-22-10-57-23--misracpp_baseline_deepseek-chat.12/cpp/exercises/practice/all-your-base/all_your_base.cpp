#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base, 
                                  const std::vector<unsigned int>& input_digits, 
                                  unsigned int output_base) {
    // Check for valid bases
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check if all digits are valid for the input base
    for (unsigned int digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Handle the case where the number is zero - according to tests, return empty vector
    // Check if all digits are zero or if the input is empty
    bool all_zero = true;
    for (unsigned int digit : input_digits) {
        if (digit != 0) {
            all_zero = false;
            break;
        }
    }
    // If input is empty or all digits are zero, return empty vector
    if (input_digits.empty() || all_zero) {
        return std::vector<unsigned int>();
    }
    
    // Convert by repeatedly dividing by output_base
    std::vector<unsigned int> result;
    std::vector<unsigned int> digits = input_digits;
    
    while (digits.size() > 0) {
        // Perform division of digits by output_base
        unsigned long long remainder = 0;
        std::vector<unsigned int> quotient;
        
        for (unsigned int digit : digits) {
            unsigned long long temp = remainder * input_base + digit;
            unsigned int q = temp / output_base;
            remainder = temp % output_base;
            
            // Push back the quotient digit if it's not leading zero or if quotient is not empty
            if (!quotient.empty() || q != 0) {
                quotient.push_back(q);
            }
        }
        
        // The remainder is our next digit in the result (from least significant to most)
        result.push_back(remainder);
        
        // Update digits to be the quotient for the next iteration
        digits = std::move(quotient);
    }
    
    // Reverse the result to get the most significant digit first
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
