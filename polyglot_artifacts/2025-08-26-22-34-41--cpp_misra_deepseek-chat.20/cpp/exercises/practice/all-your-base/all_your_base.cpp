#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

digits_t convert(base_t input_base,
                 const digits_t& input_digits,
                 base_t output_base) {
    // Check if bases are valid
    if (input_base < 2) {
        throw std::invalid_argument("Input base must be at least 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("Output base must be at least 2");
    }
    
    // Handle empty input case
    if (input_digits.empty()) {
        return digits_t();
    }
    
    // Check all digits are valid
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("All digits must be less than the input base");
        }
    }
    
    // Convert the number to base 10
    large_int_t num = 0;
    for (const auto& digit : input_digits) {
        num = (num * static_cast<large_int_t>(input_base)) + static_cast<large_int_t>(digit);
    }
    
    // Handle zero
    if (num == 0) {
        return digits_t{static_cast<digit_t>(0)};
    }
    
    // Convert to the target base
    digits_t result;
    while (num > 0) {
        result.push_back(static_cast<digit_t>(num % static_cast<large_int_t>(output_base)));
        num /= static_cast<large_int_t>(output_base);
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
