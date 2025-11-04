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
    
    // Check for valid digits
    for (unsigned int digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Handle the case when all digits are zero or input is empty
    // First, check if the number is actually zero
    // To do this, we need to see if all digits are zero or the list is empty
    bool all_zeros = true;
    for (unsigned int digit : input_digits) {
        if (digit != 0) {
            all_zeros = false;
            break;
        }
    }
    if (all_zeros || input_digits.empty()) {
        return std::vector<unsigned int>();
    }
    
    // Convert to base 10
    unsigned long long number = 0;
    for (unsigned int digit : input_digits) {
        number = number * input_base + digit;
    }
    
    // Convert to output base
    std::vector<unsigned int> output_digits;
    while (number > 0) {
        output_digits.push_back(number % output_base);
        number /= output_base;
    }
    
    // Reverse to get the correct order
    std::reverse(output_digits.begin(), output_digits.end());
    
    return output_digits;
}

}  // namespace all_your_base
