#include "all_your_base.h"

#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(
    unsigned int from_base,
    const std::vector<unsigned int>& digits,
    unsigned int to_base) {
    if (from_base < 2) {
        throw std::invalid_argument("from_base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("to_base must be >= 2");
    }
    // Check for invalid digits
    for (auto d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("all digits must be < from_base");
        }
    }
    // Remove leading zeros
    auto first_nonzero = std::find_if(digits.begin(), digits.end(), [](unsigned int d) { return d != 0; });
    std::vector<unsigned int> clean_digits(first_nonzero, digits.end());
    if (clean_digits.empty()) {
        return {};
    }

    // Convert input digits to an integer value
    unsigned long long value = 0;
    for (auto d : clean_digits) {
        value = value * from_base + d;
    }

    // Convert integer value to output base
    std::vector<unsigned int> result;
    if (value == 0) {
        return {0};
    }
    while (value > 0) {
        result.push_back(value % to_base);
        value /= to_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
