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
    
    // Check if all digits are valid for the input base
    for (unsigned int digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert to a number by summing each digit multiplied by the appropriate power of input_base
    unsigned long long number = 0;
    for (unsigned int digit : input_digits) {
        number = number * input_base + digit;
    }
    
    // Handle the case when number is 0 - return empty vector
    if (number == 0) {
        return std::vector<unsigned int>();
    }
    
    // Convert to output base
    std::vector<unsigned int> output_digits;
    while (number > 0) {
        output_digits.push_back(number % output_base);
        number /= output_base;
    }
    std::reverse(output_digits.begin(), output_digits.end());
    
    return output_digits;
}

}  // namespace all_your_base
