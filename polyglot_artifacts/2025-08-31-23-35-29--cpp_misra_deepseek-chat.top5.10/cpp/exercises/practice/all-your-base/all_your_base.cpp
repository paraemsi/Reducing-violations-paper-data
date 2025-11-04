#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<u32> convert(u32 input_base,
                         const std::vector<u32>& digits,
                         u32 output_base) {
    // Check if bases are valid
    if ((input_base < 2U)) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if ((output_base < 2U)) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Check if digits are valid
    for (const auto& digit : digits) {
        if ((digit >= input_base)) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Convert to number using a large enough type to prevent overflow
    std::uint64_t number = 0U;
    for (const auto& digit : digits) {
        number = ((number * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit));
    }
    
    // Handle the case when number is 0
    if ((number == 0U)) {
        // If the input is empty, return empty, otherwise return {0}
        if (digits.empty()) {
            return std::vector<u32>();
        } else {
            return std::vector<u32>{0U};
        }
    }
    
    // Convert number to output base digits
    std::vector<u32> result;
    while ((number > 0U)) {
        result.insert(result.begin(), static_cast<u32>((number % static_cast<std::uint64_t>(output_base))));
        number = (number / static_cast<std::uint64_t>(output_base));
    }
    
    return result;
}

}  // namespace all_your_base
