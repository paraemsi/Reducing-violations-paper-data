#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base, 
                                  const std::vector<unsigned int>& input_digits, 
                                  unsigned int output_base) {
    // Check for valid bases first
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Handle empty input - according to tests, return empty vector
    if (input_digits.empty()) {
        return std::vector<unsigned int>();
    }
    
    // Check if all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Convert the number to base 10
    unsigned long long num = 0;
    for (const auto& digit : input_digits) {
        num = num * input_base + digit;
    }
    
    // If the number is zero, return empty according to tests
    if (num == 0) {
        return std::vector<unsigned int>();
    }
    
    // Convert to the output base
    std::vector<unsigned int> result;
    while (num > 0) {
        result.push_back(num % output_base);
        num /= output_base;
    }
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
