#include "all_your_base.h"

#include <stdexcept>

namespace all_your_base {

std::vector<digit_t> convert(digit_t input_base, const std::vector<digit_t>& digits, digit_t output_base)
{
    // Validate bases
    if((input_base < static_cast<digit_t>(2)) || (output_base < static_cast<digit_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Remove leading zeros
    std::vector<digit_t>::const_iterator it = digits.begin();
    while((it != digits.end()) && ((*it) == static_cast<digit_t>(0))) {
        ++it;
    }
    std::vector<digit_t> clean_digits(it, digits.end());

    if(clean_digits.empty()) {
        // Zero is represented as {0}
        return std::vector<digit_t>{static_cast<digit_t>(0)};
    }

    // Validate digits
    for(std::vector<digit_t>::const_iterator d = clean_digits.begin(); d != clean_digits.end(); ++d) {
        if((*d) >= input_base) {
            throw std::invalid_argument("All digits must be < input base");
        }
    }

    // Convert input digits to integer value
    std::uint64_t value = static_cast<std::uint64_t>(0);
    for(std::vector<digit_t>::const_iterator d = clean_digits.begin(); d != clean_digits.end(); ++d) {
        value = (value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(*d);
    }

    // Convert integer value to output base
    std::vector<digit_t> result;
    while(value > static_cast<std::uint64_t>(0)) {
        digit_t rem = static_cast<digit_t>(value % static_cast<std::uint64_t>(output_base));
        result.insert(result.begin(), rem);
        value = value / static_cast<std::uint64_t>(output_base);
    }

    return result;
}

}  // namespace all_your_base
