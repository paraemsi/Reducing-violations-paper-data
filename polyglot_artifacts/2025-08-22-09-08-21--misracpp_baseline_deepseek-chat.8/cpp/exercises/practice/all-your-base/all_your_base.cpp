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
    
    // Handle the case where input is empty
    if (input_digits.empty()) {
        return {};
    }
    
    // Check if all digits are zero - according to tests, we should return empty vector
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
    
    // Convert using a method that doesn't rely on a single number to prevent overflow
    std::vector<unsigned int> result;
    std::vector<unsigned int> digits(input_digits.begin(), input_digits.end());
    
    while (digits.size() > 0) {
        // Perform division of the digits by output_base
        unsigned long long remainder = 0;
        std::vector<unsigned int> quotient;
        
        for (unsigned int digit : digits) {
            unsigned long long temp = remainder * input_base + digit;
            quotient.push_back(temp / output_base);
            remainder = temp % output_base;
        }
        
        // The remainder is the next digit in the result
        result.push_back(remainder);
        
        // Remove leading zeros from quotient
        digits.clear();
        bool found_non_zero = false;
        for (unsigned int digit : quotient) {
            if (digit != 0 || found_non_zero) {
                found_non_zero = true;
                digits.push_back(digit);
            }
        }
    }
    
    // Reverse the result to get the correct order
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
