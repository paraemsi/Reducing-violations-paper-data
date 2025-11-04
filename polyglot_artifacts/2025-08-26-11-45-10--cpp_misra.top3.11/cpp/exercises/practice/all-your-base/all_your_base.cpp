#include "all_your_base.h"
#include <stdexcept>

namespace all_your_base {

auto convert(std::int32_t input_base, std::vector<int> const& input_digits, std::int32_t output_base) -> std::vector<int>
{
    // Validate bases
    if((input_base < 2) || (output_base < 2)) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate input digits
    if(input_digits.empty()) {
        return std::vector<int>{0};
    }

    bool all_zero = true;
    for(const auto digit : input_digits) {
        if((digit < 0) || (digit >= input_base)) {
            throw std::invalid_argument("Invalid digit in input");
        }
        if(digit != 0) {
            all_zero = false;
        }
    }
    if(all_zero) {
        return std::vector<int>{0};
    }

    // Convert input digits to integer value
    std::vector<int>::const_iterator it = input_digits.begin();
    std::uint64_t value = 0U;
    for(; it != input_digits.end(); ++it) {
        value = (value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(*it);
    }

    // Convert integer value to output_base digits
    std::vector<int> output_digits;
    while(value > 0U) {
        output_digits.insert(output_digits.begin(), static_cast<int>(value % static_cast<std::uint64_t>(output_base)));
        value = value / static_cast<std::uint64_t>(output_base);
    }

    return output_digits;
}

}  // namespace all_your_base
