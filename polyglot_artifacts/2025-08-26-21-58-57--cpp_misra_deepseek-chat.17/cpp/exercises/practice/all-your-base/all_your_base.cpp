#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

std::vector<unsigned int> convert(int input_base, 
                                  const std::vector<unsigned int>& input_digits, 
                                  int output_base) {
    // Check if bases are valid
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check if all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= static_cast<unsigned int>(input_base)) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Convert input digits to a number
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        number = number * static_cast<std::uint64_t>(input_base) + static_cast<std::uint64_t>(digit);
    }
    
    // If the number is zero, return an empty vector
    if (number == 0) {
        return std::vector<unsigned int>();
    }
    
    // Convert the number to the output base
    std::vector<unsigned int> output_digits;
    while (number > 0) {
        output_digits.insert(output_digits.begin(), static_cast<unsigned int>(number % static_cast<std::uint64_t>(output_base)));
        number /= static_cast<std::uint64_t>(output_base);
    }
    
    return output_digits;
}

}  // namespace all_your_base
