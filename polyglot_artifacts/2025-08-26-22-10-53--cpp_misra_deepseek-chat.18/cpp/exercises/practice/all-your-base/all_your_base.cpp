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
    if ((input_base < 2) || (output_base < 2)) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check if input digits are valid
    for (std::uint32_t digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert input digits to a number
    std::int64_t number = 0;
    for (std::uint32_t digit : input_digits) {
        number = ((number * static_cast<std::int64_t>(input_base)) + static_cast<std::int64_t>(digit));
    }
    
    // Handle the case when number is 0 - return an empty vector
    if (number == 0) {
        return std::vector<std::uint32_t>();
    }
    
    // Convert the number to output base digits
    std::vector<std::uint32_t> output_digits;
    while (number > 0) {
        std::int64_t remainder = (number % static_cast<std::int64_t>(output_base));
        output_digits.push_back(static_cast<std::uint32_t>(remainder));
        number = (number / static_cast<std::int64_t>(output_base));
    }
    
    // The digits are in reverse order
    std::reverse(output_digits.begin(), output_digits.end());
    
    return output_digits;
}

}  // namespace all_your_base
