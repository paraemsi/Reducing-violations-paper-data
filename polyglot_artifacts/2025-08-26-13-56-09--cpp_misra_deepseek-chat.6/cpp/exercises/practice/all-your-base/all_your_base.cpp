#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <limits>

namespace all_your_base {

std::vector<udigit_t> convert(ubase_t input_base,
                              const std::vector<udigit_t>& input_digits,
                              ubase_t output_base) {
    // Handle empty input
    if (input_digits.empty()) {
        return std::vector<udigit_t>();
    }
    
    // Check for valid bases
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Check all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert the input digits to a number
    // Use a large enough type to handle potential large numbers
    // Since we need to follow MISRA, we'll use a fixed-width type
    std::uint64_t number = 0;
    for (const auto& digit : input_digits) {
        // Check for potential overflow
        if (number > (std::numeric_limits<std::uint64_t>::max() - static_cast<std::uint64_t>(digit)) / static_cast<std::uint64_t>(input_base)) {
            throw std::overflow_error("number too large to represent");
        }
        number = number * static_cast<std::uint64_t>(input_base) + static_cast<std::uint64_t>(digit);
    }
    
    // Handle the case when number is 0
    if (number == 0) {
        return std::vector<udigit_t>{0};
    }
    
    // Convert to output base
    std::vector<udigit_t> output_digits;
    while (number > 0) {
        output_digits.insert(output_digits.begin(), static_cast<udigit_t>(number % static_cast<std::uint64_t>(output_base)));
        number /= static_cast<std::uint64_t>(output_base);
    }
    
    return output_digits;
}

}  // namespace all_your_base
