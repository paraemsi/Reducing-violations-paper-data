#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, 
                                   const std::vector<std::uint32_t>& input_digits, 
                                   std::uint32_t output_base) {
    // Handle invalid bases
    if (input_base < 2) {
        throw std::invalid_argument("Input base must be at least 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("Output base must be at least 2");
    }
    
    // Check if input_digits is empty - treat it as 0
    // But according to the tests, we need to always return [0] when the number is zero
    // So we can process it normally
    
    // Check all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Convert the number to a value
    std::uint64_t num = 0;
    for (const auto& digit : input_digits) {
        num = (num * input_base) + digit;
    }
    
    // If the number is zero, return an empty vector to match the tests
    if (num == 0) {
        return {};
    }
    
    // Convert to the target base
    std::vector<std::uint32_t> result;
    while (num > 0) {
        result.insert(result.begin(), static_cast<std::uint32_t>(num % output_base));
        num /= output_base;
    }
    
    return result;
}

}  // namespace all_your_base
