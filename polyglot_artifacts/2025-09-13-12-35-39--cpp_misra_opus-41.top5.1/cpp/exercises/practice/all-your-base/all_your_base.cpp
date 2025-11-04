#include "all_your_base.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base, const std::vector<std::uint32_t>& input_digits, std::uint32_t output_base) {
    // Validate bases - must be at least 2
    if ((input_base < 2U) || (output_base < 2U)) {
        throw std::invalid_argument("Invalid base");
    }
    
    // Check for invalid digits in input
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("Invalid digit");
        }
    }
    
    // Handle empty input
    if (input_digits.empty()) {
        return {};
    }
    
    // Convert from input base to decimal
    std::uint64_t decimal_value = 0U;
    std::uint64_t base_power = 1U;
    
    // Process digits from right to left
    for (auto it = input_digits.rbegin(); it != input_digits.rend(); ++it) {
        std::uint64_t digit_value = *it;
        decimal_value = decimal_value + (digit_value * base_power);
        base_power = base_power * static_cast<std::uint64_t>(input_base);
    }
    
    // Handle zero case - return empty vector for zero
    if (decimal_value == 0U) {
        return {};
    }
    
    // Convert from decimal to output base
    std::vector<std::uint32_t> result;
    
    while (decimal_value > 0U) {
        std::uint64_t remainder = decimal_value % static_cast<std::uint64_t>(output_base);
        result.push_back(static_cast<std::uint32_t>(remainder));
        decimal_value = decimal_value / static_cast<std::uint64_t>(output_base);
    }
    
    // Reverse to get most significant digit first
    std::reverse(result.begin(), result.end());
    
    return result;
}

}  // namespace all_your_base
