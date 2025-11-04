#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint8_t> convert(unsigned int input_base, 
                                  const std::vector<unsigned int>& input_digits,
                                  unsigned int output_base) {
    // Convert parameters to fixed-width types to comply with rules
    const base_t in_base = static_cast<base_t>(input_base);
    const base_t out_base = static_cast<base_t>(output_base);
    
    // Check if bases are valid
    if (in_base < 2U) {
        throw std::invalid_argument("Input base must be at least 2");
    }
    if (out_base < 2U) {
        throw std::invalid_argument("Output base must be at least 2");
    }
    
    // Check if digits are valid
    for (const auto& digit : input_digits) {
        const digit_t current_digit = static_cast<digit_t>(digit);
        if (current_digit >= in_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Convert to a number
    std::uint64_t num = 0U;
    for (const auto& digit : input_digits) {
        const digit_t current_digit = static_cast<digit_t>(digit);
        num = (num * static_cast<std::uint64_t>(in_base)) + static_cast<std::uint64_t>(current_digit);
    }
    
    // Handle the case when number is zero
    if (num == 0U) {
        if (input_digits.empty()) {
            return {};
        } else {
            return {0U};
        }
    }
    
    // Convert to output base
    std::vector<std::uint8_t> result;
    while (num > 0U) {
        result.insert(result.begin(), static_cast<std::uint8_t>(num % static_cast<std::uint64_t>(out_base)));
        num /= static_cast<std::uint64_t>(out_base);
    }
    
    return result;
}

}  // namespace all_your_base
