#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base,
                                   const std::vector<std::uint32_t>& input_digits,
                                   std::uint32_t output_base) {
    // Check for valid bases
    if ((input_base < 2) || (output_base < 2)) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    
    // Check if all digits are valid for the input base
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must satisfy 0 <= d < input base");
        }
    }
    
    // Handle cases where the number is zero (empty input or all zeros)
    // Check if all digits are zero or input is empty
    bool all_zeros = true;
    for (const auto& digit : input_digits) {
        if (digit != 0) {
            all_zeros = false;
            break;
        }
    }
    if (all_zeros || input_digits.empty()) {
        return std::vector<std::uint32_t>{};
    }
    
    // Convert the number to base 10
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        // Check for potential overflow before multiplying
        if (number > ((static_cast<std::uint64_t>(-1)) - static_cast<std::uint64_t>(digit)) / static_cast<std::uint64_t>(input_base)) {
            throw std::overflow_error("Number too large to represent");
        }
        number = (number * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }
    
    // Convert to output base
    std::vector<std::uint32_t> output_digits;
    while (number > 0) {
        // Insert the remainder at the beginning
        output_digits.insert(output_digits.begin(), static_cast<std::uint32_t>(number % static_cast<std::uint64_t>(output_base)));
        number /= static_cast<std::uint64_t>(output_base);
    }
    
    return output_digits;
}

}  // namespace all_your_base
