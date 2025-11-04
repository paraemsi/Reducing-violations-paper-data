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
    
    // Handle the case when input is empty
    if (input_digits.empty()) {
        return std::vector<unsigned int>();
    }
    
    // Check if all digits are zero
    bool all_zeros = true;
    for (unsigned int digit : input_digits) {
        if (digit != 0) {
            all_zeros = false;
            break;
        }
    }
    if (all_zeros) {
        return std::vector<unsigned int>();
    }
    
    // Convert using a method that doesn't risk integer overflow
    std::vector<unsigned int> result;
    std::vector<unsigned int> digits(input_digits.begin(), input_digits.end());
    
    while (!digits.empty()) {
        unsigned int remainder = 0;
        std::vector<unsigned int> quotient;
        
        // Perform division digit by digit
        for (unsigned int digit : digits) {
            unsigned int temp = remainder * input_base + digit;
            quotient.push_back(temp / output_base);
            remainder = temp % output_base;
        }
        
        // The remainder is the next digit in the result
        result.push_back(remainder);
        
        // Remove leading zeros from quotient
        digits.clear();
        auto it = quotient.begin();
        while (it != quotient.end() && *it == 0) {
            ++it;
        }
        for (; it != quotient.end(); ++it) {
            digits.push_back(*it);
        }
    }
    
    // Reverse to get the correct order
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
