#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base, 
                                  const std::vector<unsigned int>& input_digits, 
                                  unsigned int output_base) {
    // Validate bases
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check if input_digits is empty - return empty
    if (input_digits.empty()) {
        return {};
    }
    
    // Validate all digits are valid for the input base
    for (unsigned int digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Convert the number to a value (base 10)
    unsigned long long number = 0;
    for (unsigned int digit : input_digits) {
        number = number * input_base + digit;
    }
    
    // Handle the case when number is zero - return empty vector
    if (number == 0) {
        return {};
    }
    
    // Convert to the output base
    std::vector<unsigned int> result;
    while (number > 0) {
        result.push_back(number % output_base);
        number /= output_base;
    }
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
