#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base, 
                                  const std::vector<unsigned int>& input_digits,
                                  unsigned int output_base) {
    // Validate bases
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Handle empty input
    if (input_digits.empty()) {
        return {};
    }
    
    // Validate input digits
    for (unsigned int digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must be < input base");
        }
    }
    
    // Convert from input base to decimal
    unsigned long long decimal_value = 0;
    unsigned long long power = 1;
    
    // Process digits from right to left
    for (auto it = input_digits.rbegin(); it != input_digits.rend(); ++it) {
        decimal_value += (*it) * power;
        power *= input_base;
    }
    
    // Handle the special case of zero (including leading zeros)
    if (decimal_value == 0) {
        return {};
    }
    
    // Convert from decimal to output base
    std::vector<unsigned int> result;
    while (decimal_value > 0) {
        result.push_back(decimal_value % output_base);
        decimal_value /= output_base;
    }
    
    // Reverse to get most significant digit first
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
