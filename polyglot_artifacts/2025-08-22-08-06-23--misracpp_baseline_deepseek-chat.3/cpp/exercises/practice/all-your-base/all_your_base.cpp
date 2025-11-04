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
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Handle cases where the number is zero - according to tests, return an empty vector
    // Check if all digits are zero or input is empty
    bool all_zeros = true;
    for (unsigned int digit : input_digits) {
        if (digit != 0) {
            all_zeros = false;
            break;
        }
    }
    if (input_digits.empty() || all_zeros) {
        return {};
    }
    
    // To avoid overflow, we'll process the digits directly
    std::vector<unsigned int> result;
    
    // Make a copy of input digits to process
    std::vector<unsigned int> digits(input_digits);
    
    while (!digits.empty()) {
        // Perform division of digits by output_base
        unsigned int remainder = 0;
        std::vector<unsigned int> quotient;
        
        for (unsigned int digit : digits) {
            unsigned int temp = remainder * input_base + digit;
            unsigned int q = temp / output_base;
            remainder = temp % output_base;
            
            // Push back the quotient digit if it's not leading zero or if quotient is not empty
            if (!quotient.empty() || q != 0) {
                quotient.push_back(q);
            }
        }
        
        // The remainder is our next digit (from right to left)
        result.push_back(remainder);
        
        // Update digits to be the quotient for next iteration
        digits = std::move(quotient);
    }
    
    // Reverse the result to get the correct order
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
