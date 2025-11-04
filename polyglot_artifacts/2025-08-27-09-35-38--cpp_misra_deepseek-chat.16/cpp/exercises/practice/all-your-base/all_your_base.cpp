#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base,
                                   const std::vector<std::uint32_t>& input_digits,
                                   std::uint32_t output_base) {
    // Check if bases are valid
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Handle empty input digits by returning an empty vector
    if (input_digits.empty()) {
        return std::vector<std::uint32_t>{};
    }
    
    // Check if all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert to a number (treated as base 10 for intermediate calculation)
    std::uint64_t num = 0;
    for (const auto& digit : input_digits) {
        num = (num * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }
    
    // Handle the case when number is zero - return empty vector
    if (num == 0) {
        return std::vector<std::uint32_t>{};
    }
    
    // Convert from the number to the output base
    std::vector<std::uint32_t> result;
    while (num > 0) {
        result.insert(result.begin(), static_cast<std::uint32_t>(num % static_cast<std::uint64_t>(output_base)));
        num /= static_cast<std::uint64_t>(output_base);
    }
    
    return result;
}

}  // namespace all_your_base
