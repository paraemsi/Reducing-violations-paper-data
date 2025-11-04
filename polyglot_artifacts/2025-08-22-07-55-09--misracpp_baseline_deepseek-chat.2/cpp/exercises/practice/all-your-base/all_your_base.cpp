#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int source_base, 
                                  const std::vector<unsigned int>& digits, 
                                  unsigned int target_base) {
    // Check for valid bases
    if (source_base < 2 || target_base < 2) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check if all digits are valid for the source base
    for (unsigned int digit : digits) {
        if (digit >= source_base) {
            throw std::invalid_argument("All digits must be less than the source base");
        }
    }
    
    // Handle the case where all digits are zero or input is empty
    // First, check if the number is actually zero
    // To do this, we need to process the digits to see if they represent zero
    // But since leading zeros are valid, we need to check if all digits are zero
    bool all_zeros = true;
    for (unsigned int digit : digits) {
        if (digit != 0) {
            all_zeros = false;
            break;
        }
    }
    
    // If all digits are zero, return an empty vector
    if (digits.empty() || all_zeros) {
        return std::vector<unsigned int>();
    }
    
    // Convert to a number by processing each digit
    unsigned long long number = 0;
    for (unsigned int digit : digits) {
        number = number * source_base + digit;
    }
    
    // Convert to target base
    std::vector<unsigned int> result;
    while (number > 0) {
        result.push_back(number % target_base);
        number /= target_base;
    }
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
