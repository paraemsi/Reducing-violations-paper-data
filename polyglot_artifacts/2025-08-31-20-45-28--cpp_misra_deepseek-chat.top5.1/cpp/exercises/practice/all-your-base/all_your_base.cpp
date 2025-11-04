#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<digit_t> convert(base_t input_base,
                             const std::vector<digit_t>& input_digits,
                             base_t output_base) {
    // Check if bases are valid
    if ((input_base < 2U)) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if ((output_base < 2U)) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Check if all digits are valid
    for (const auto& digit : input_digits) {
        if ((digit >= input_base)) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Handle empty input digits - return empty result
    if (input_digits.empty()) {
        return std::vector<digit_t>{};
    }
    
    // Convert to a number
    std::uint64_t number = 0U;
    for (const auto& digit : input_digits) {
        number = ((number * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit));
    }
    
    // Handle the case when number is zero - return empty result
    if ((number == 0U)) {
        return std::vector<digit_t>{};
    }
    
    // Convert to output base
    std::vector<digit_t> result;
    while ((number > 0U)) {
        result.insert(result.begin(), static_cast<digit_t>((number % static_cast<std::uint64_t>(output_base))));
        number = (number / static_cast<std::uint64_t>(output_base));
    }
    
    return result;
}

}  // namespace all_your_base
