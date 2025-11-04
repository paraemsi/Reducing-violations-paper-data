#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base, 
                                  const std::vector<unsigned int>& input_digits, 
                                  unsigned int output_base) {
    // Check if bases are valid
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Handle empty input digits
    if (input_digits.empty()) {
        return {};
    }
    
    // Check if all digits are valid
    for (unsigned int digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must satisfy 0 <= digit < input base");
        }
    }
    
    // Convert input digits to a number by processing each digit
    // Skip leading zeros to avoid unnecessary processing
    unsigned long long number = 0;
    bool non_zero_found = false;
    for (unsigned int digit : input_digits) {
        // Once we find a non-zero digit, all following digits matter
        if (digit != 0) {
            non_zero_found = true;
        }
        if (non_zero_found) {
            number = number * input_base + digit;
        }
    }
    
    // If the number is zero (all input digits were zero), return empty vector
    if (number == 0) {
        return {};
    }
    
    // Convert number to output base
    std::vector<unsigned int> output_digits;
    while (number > 0) {
        output_digits.insert(output_digits.begin(), number % output_base);
        number /= output_base;
    }
    
    return output_digits;
}

}  // namespace all_your_base
