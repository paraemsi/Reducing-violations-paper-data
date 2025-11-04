#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base,
                                   const std::vector<std::uint32_t>& input_digits,
                                   std::uint32_t output_base) {
    // Check for valid bases
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Check if input digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Handle the case when there are no input digits
    if (input_digits.empty()) {
        return {};
    }
    
    // First, check if the number is zero (all digits are zero)
    // According to the test, we should return an empty vector in this case
    bool all_zeros = true;
    for (const auto& digit : input_digits) {
        if (digit != 0) {
            all_zeros = false;
            break;
        }
    }
    if (all_zeros) {
        return {};
    }
    
    // Convert the number to the output base
    std::vector<std::uint32_t> result;
    // To avoid dealing with large numbers, we'll process the digits directly
    // Make a copy of the input digits to work with
    std::vector<std::uint32_t> current_digits(input_digits.begin(), input_digits.end());
    
    while (!current_digits.empty()) {
        std::uint32_t remainder = 0;
        std::vector<std::uint32_t> quotient;
        
        // Process each digit
        for (const auto& digit : current_digits) {
            std::uint32_t value = (remainder * input_base) + digit;
            std::uint32_t q = value / output_base;
            remainder = value % output_base;
            // Add to quotient if it's not leading zero or if the quotient is not empty
            if ((!quotient.empty()) || (q != 0)) {
                quotient.push_back(q);
            }
        }
        // The remainder is our next digit in the result
        result.push_back(remainder);
        // Update current_digits to be the quotient for the next iteration
        current_digits = std::move(quotient);
    }
    
    // The digits are in reverse order
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
